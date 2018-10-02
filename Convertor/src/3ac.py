import sys
from pycparser import c_ast, parse_file, c_generator


PROCESS_LOOP_RELEASE = False
NAMESPACE = "__pool__"
XOR_name = "XOR"
AND_name = "AND"
RELEASE_fcall = NAMESPACE + "RELEASE"
COPY_fcall = NAMESPACE + "COPY"
NEWVAR_fcall = NAMESPACE + "NewVar"
NEWARR_fcall = NAMESPACE + "NewArray"
RELEASEARR_fcall = NAMESPACE + "RELEASEArray"
XOR_fcall = NAMESPACE + XOR_name
AND_fcall = NAMESPACE + AND_name
BIT_type = "bit"
INDEX_type = "Index"
POOL_types = [BIT_type, INDEX_type]


def unzip(lst, pos):
    itms = []
    for itm in lst:
        res = itm[pos]
        if isinstance(res, list):
            itms.extend(res)
        else:
            itms.append(res)
    return itms

def copy(lst):
    return [x for x in lst]

def join_type(types):
    return "".join(types)

def ids_of_type(table, scope, c_types):
    res = [x[0] for x in table.get(scope, [])
            if x[1] in c_types]
    params = [x[0] for x in table.getParam(scope, [])
                if x[1] in c_types]
    return res, params

def ids_of_type2(table, scope, c_types):
    res = [x[0] for x in table.getNested(scope, [])
           if x[1] in c_types]
    return res

def ids_of_type3(table, scope, c_types):
    res = [x[0] for x in table.getParam(scope, [])
           if x[1] in c_types]
    return res

def arrays_of_type(table, scope, c_types):
    res = [(x[0], x[3]) for x in table.get(scope, [])
           if x[1] in c_types and 
           isinstance(x[3], c_ast.ArrayDecl)]
    res.extend([(x[0], x[3]) for x in table.getParam(scope, [])
              if x[1] in c_types and 
              isinstance(x[3], c_ast.ArrayDecl)])
    res.extend([(x[0], x[3]) for x in table.getNested(scope, [])
           if x[1] in c_types and 
           isinstance(x[3], c_ast.ArrayDecl)])
    return res

def new_var(name):
    var = c_ast.ID(name)
    return var

def new_ivar(name, p_type=BIT_type):
    var_type = c_ast.IdentifierType([p_type])
    decl_type = c_ast.TypeDecl(name, [], var_type)
    var = c_ast.Decl(name, [], [], [], decl_type, None, None)
    return var

def new_fcall(fname, args):
    fname = c_ast.ID(fname)
    args_list = []
    for arg in args:
        if isinstance(arg, str):
            args_list.append(c_ast.ID(arg))
        else:
            args_list.append(arg)
    args = c_ast.ExprList(args_list)
    return c_ast.FuncCall(fname, args)

def new_const(c_type, val):
    return c_ast.Constant(c_type, val)

def new_condop(c_type, op, lval, rval):
    return c_ast.BinaryOp(op, lval, rval)

def new_if(cond, iftrue, iffalse):
    return c_ast.If(cond, iftrue, iffalse)


class FCallVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = []

    def visit_FuncCall(self, node):
        self.result.append(node.name.name)


class IDVisitor(c_ast.NodeVisitor):
    def __init__(self, func=None, args=[]):
        self.result = []
        self.func = func
        self.args = args

    def visit_ID(self, node):
        self.func(node, self.args)


class AssignmentVisitor(c_ast.NodeVisitor):
    def __init__(self, func=None, args=[]):
        self.result = []
        self.func = func
        self.args = args

    def visit_Assignment(self, node):
        if self.func:
            self.result.append(self.func(node, self.args))


class VarDeclVisitor(c_ast.NodeVisitor):
    def __init__(self, types=[], func=None, args=[]):
        self.result = []
        self.types = types
        self.func = func
        self.args = args

    def visit_Decl(self, node):
        if self.func:
            self.func(node, self.args)
        if isinstance(node.type, c_ast.TypeDecl):
            var_type = join_type(node.type.type.names)
            if var_type in self.types:
                self.result.append((node.name, var_type, node.init, node.type))
        elif isinstance(node.type, c_ast.ArrayDecl):
            i_type = node.type.type.type
            if isinstance(i_type, c_ast.TypeDecl):
                var_type = join_type(i_type.type.names)
            else:
                var_type = join_type(i_type.names)
            if var_type in self.types:
                self.result.append((node.name, var_type, node.init, node.type))


class ThreeACTransform(c_ast.NodeVisitor):
    """ Handles 3 Address Code transformation """
    def __init__(self):
        self.ctr = 0

    def FuncCall(self, node, parent, new_items):
        to_transform = [XOR_name, AND_name]
        # transform_args = False
        transform_exprs = []
        if hasattr(node, "args") and node.args is not None:
            for indx, expr in enumerate(node.args.exprs):
                name = expr.__class__.__name__
                if name == "FuncCall":
                    if expr.name.name in to_transform:
                        # transform_args = True
                        transform_exprs.append((indx, expr))
        # Change to 'if True' to rewrite all funcs
        # (currently just rewriting xor and and)
        # node.name.name in to_transform or transform_args:
        if True:
            var_name = "__tmp__" + str(self.ctr)
            tmp_var = new_ivar(var_name)
            for indx, expr in transform_exprs:
                self.ctr += 1
                new_items, expr, rewrite = \
                    self.FuncCall(expr, parent, new_items)
                if rewrite:
                    node.args.exprs[indx] = expr
            # Changed to decl w/ init rather than assign(decl, node)
            tmp_var.init = node
            new_node = tmp_var
            # new_node = c_ast.Assignment("=", tmp_var, node, None)
            new_items.append(new_node)
            return new_items, c_ast.ID(var_name), True
        new_items.append(node)
        return new_items, None, False

    def threeac(self, name, itm, node, new_items):
        if name == "FuncCall":
            new_items, _, _ = self.FuncCall(itm, node, new_items)
            new_items.pop()
            new_items.append(itm)
        elif name == "Decl":
            if itm.init is not None and itm.init.__class__.__name__ == "FuncCall":
                new_items, init, rewrite = \
                    self.FuncCall(itm.init, node, new_items)
                if rewrite:
                    itm.init = init
            new_items.append(itm)
        elif name == "Assignment":
            if itm.rvalue is not None and itm.rvalue.__class__.__name__ == "FuncCall":
                old_items = copy(new_items)
                new_items, rvalue, rewrite = \
                    self.FuncCall(itm.rvalue, node, new_items)
                if rewrite:
                    itm.rvalue = rvalue
                else:
                    new_items = old_items
            new_items.append(itm)
        elif name == "Return":
            if itm.expr is not None and itm.expr.__class__.__name__ == "FuncCall":
                old_items = copy(new_items)
                new_items, expr, rewrite = \
                    self.FuncCall(itm.expr, node, new_items)
                if rewrite:
                    itm.expr = expr
                else:
                    var_name = "__tmp__" + str(self.ctr)
                    tmp_var = new_ivar(var_name)
                    # Changed to decl w/ init rather than assign(decl, node)
                    tmp_var.init = itm.expr
                    new_node = tmp_var
                    # new_node = c_ast.Assignment("=", tmp_var, itm.expr, None)
                    new_items = old_items
                    new_items.append(new_node)
                    itm.expr = new_var(var_name)
            new_items.append(itm)
        return new_items

    def visit_Compound(self, node):
        new_items = []
        to_trans = ["FuncCall", "Decl", "Assignment", "Return"]
        if hasattr(node, "block_items") and node.block_items is not None:
            for itm in node.block_items:
                self.ctr += 1
                name = itm.__class__.__name__
                if isinstance(itm, c_ast.For):
                    if itm.stmt is not None:
                        if isinstance(itm.stmt, c_ast.Compound):
                            self.visit_Compound(itm.stmt)
                        else:
                            new_items = \
                                self.threeac(name, itm.stmt, node, new_items)
                        new_items.append(itm)
                elif isinstance(itm, c_ast.If):
                    if itm.iftrue is not None:
                        if isinstance(itm.iftrue, c_ast.Compound):
                            self.visit_Compound(itm.iftrue)
                    if itm.iffalse is not None:
                        if isinstance(itm.iffalse, c_ast.Compound):
                            self.visit_Compound(itm.iffalse)
                    if itm.iftrue or itm.iffalse:
                        new_items.append(itm)
                elif isinstance(itm, c_ast.While):
                    if itm.stmt is not None:
                        if isinstance(itm.stmt, c_ast.Compound):
                            self.visit_Compound(itm.stmt)
                        else:
                            new_items = \
                                self.threeac(name, itm.stmt, node, new_items)
                        new_items.append(itm)
                elif name in to_trans:
                    new_items = self.threeac(name, itm, node, new_items)
                else:
                    new_items.append(itm)
            node.block_items = new_items


class ScopeTable(object):
    def __init__(self):
        self.table = {}
    
    def get(self, scope, ret=-1):
        if scope in self.table.keys():
            return self.table[scope]
        elif ret != -1:
            return ret
        else:
            raise KeyError("Key: " + str(scope) + " not found!")
    
    def getNested(self, scope, ret=-1):
        res = []
        for k, v in self.table.items():
            key = k
            if ':' in k and 'Param' not in k:
                res.extend(v)
        if res == [] and ret != -1:
            return ret
        return res
    
    def getParam(self, scope, ret=-1):
        res = []
        for k, v in self.table.items():
            key = k
            if ':Param' in k:
                res.extend(v)
        if res == [] and ret != -1:
            return ret
        return res
    
    def __getitem__(self, k):
        return self.table[k]
    
    def __setitem__(self, k, v):
        self.table[k] = v
    
    def add(self, k, v):
        if self.table.get(k, None) is None:
            self.table[k] = [v]
        else:
            if v not in self.table[k]:
                self.table[k].append(v)


class GenerateScopeTable(c_ast.NodeVisitor):
    """ Generate a table of in-scope vars for each function.
        table[fname] = vars_in_scope
        table[fname+:Param] = function_params
        table[fname+:Block[i]] = vars_in_scope_at_block_i
    """
    def __init__(self):
        self.scope_table = ScopeTable()

    def disjoint(self, s1, s2):
        return [x for x in s1 if x not in s2]

    def inner_process(self, block, func_name):
        include = []
        dv = VarDeclVisitor([BIT_type, "int", INDEX_type])
        dv.visit(block)
        include.extend(dv.result)
        exclude = []
        if block.__class__ == c_ast.Compound:
            exclude = self.inner_visit(func_name, block)
        disjoint = [x for x in dv.result if x not in exclude]
        for var in disjoint:
            self.scope_table.add(func_name, var)
        dv.result = []
        return include

    def inner_visit(self, func_name, itm):
        include = []
        for indx, node in enumerate(itm.block_items):
            name = node.__class__.__name__
            if name == "For":
                if node.stmt is not None:
                    if node.stmt.__class__ == c_ast.Compound:
                        include.extend(self.inner_process(node.stmt, func_name+\
                                                          ":Block"+str(indx)))
            elif name == "If":
                if node.iftrue is not None:
                    if node.iftrue.__class__ == c_ast.Compound:
                        include.extend(self.inner_process(node.iftrue, func_name+\
                                                          ":Block"+str(indx)))
                if node.iffalse is not None:
                    if node.iffalse.__class__ == c_ast.Compound:
                        include.extend(self.inner_process(node.iffalse, func_name+\
                                                          ":Block"+str(indx)))
            elif name == "While":
                if node.stmt is not None:
                    if node.stmt.__class__ == c_ast.Compound:
                        include.extend(self.inner_process(node.stmt, func_name+\
                                                          ":Block"+str(indx)))
            else:
                include.extend(self.inner_process(node, func_name))
        return include

    def visit_FileAST(self, node):
        for itm in node.ext:
            itm_type = itm.__class__.__name__
            # Only includes 'bit' type variables
            dv = VarDeclVisitor([BIT_type, "int", INDEX_type])
            if itm_type == c_ast.Decl:
                var_name = itm.name
                dict_add(self.scope_table, "global", var_name)
            elif itm_type == "FuncDef":
                func_name = itm.decl.name
                if hasattr(itm.body, "block_items") and itm.body.block_items is not None:
                    # Comment out to disclude function arguments
                    if itm.decl.type.args is not None:
                        for param in itm.decl.type.args.params:
                            if isinstance(param.type, c_ast.TypeDecl):
                                param_type = join_type(param.type.type.names)
                                self.scope_table.add(func_name+":Param",
                                         (param.name, param_type, None, param.type))
                            elif isinstance(param.type, c_ast.PtrDecl):
                                param_type = join_type(param.type.type.type.names)
                                self.scope_table.add(func_name+":ParamPtr",
                                         (param.name, param_type, None, param.type))
                            elif isinstance(param.type, c_ast.ArrayDecl):
                                param_type = join_type(param.type.type.type.names)
                                self.scope_table.add(func_name+":Param",
                                         (param.name, param_type, None, param.type))
                    self.inner_visit(func_name, itm.body)


class Release1Transform(c_ast.NodeVisitor):
    """ Rule 1: call "RELEASE(x)" for each (once used for computation) local variable x
                after its last use in a scope
    """
    def __init__(self, scope_table):
        self.scope_table = scope_table

    def process_block_items(self, path, block_items):
        # path = ['root', idx_1...idx_n]
        has_return = False
        indx = 0
        returned_var = None
        for i, itm in enumerate(block_items):
            if itm.__class__ == c_ast.Return:
                has_return = True
                if itm.expr.__class__ == c_ast.ID:
                    returned_var = itm.expr.name
                indx = i
            elif itm.__class__ == c_ast.For: # and PROCESS_LOOP_RELEASE:
                if itm.stmt.__class__ == c_ast.Compound:
                    self.process_block_items(path+":Block"+str(i), itm.stmt.block_items)
            elif itm.__class__ == c_ast.While: # and PROCESS_LOOP_RELEASE:
                if itm.stmt.__class__ == c_ast.Compound:
                    self.process_block_items(path+":Block"+str(i), itm.stmt.block_items)
            elif itm.__class__ == c_ast.If:
                if itm.iftrue.__class__ == c_ast.Compound:
                    self.process_block_items(path+":Block"+str(i), itm.iftrue.block_items)
                if itm.iffalse.__class__ == c_ast.Compound:
                    self.process_block_items(path+":Block"+str(i), itm.iffalse.block_items)
        local_vars, params = ids_of_type(self.scope_table, path, POOL_types)
        arrays = arrays_of_type(self.scope_table, self.current_scope, POOL_types)
        array_names = [x[0] for x in arrays]
        if path == self.current_scope:
            local_vars.extend(params)
        local_vars_seen = []
        for var in local_vars:
            if var in local_vars_seen:
                continue
            else:
                local_vars_seen.append(var)
            release_call = None
            if var in array_names:
                idx = array_names.index(var)
                array, a_type = arrays[idx]
                if a_type.dim:
                    release_call = new_fcall(RELEASEARR_fcall, [var, a_type.dim])
            elif var in params:
                if var in self.assigned_params:
                    release_call = new_fcall(RELEASE_fcall, [var])
            else:
                release_call = new_fcall(RELEASE_fcall, [var])
            if has_return:
                # Don't release a returned variable
                if var != returned_var and release_call:
                    block_items.insert(indx, release_call)
            elif release_call:
                block_items.append(release_call)
        return block_items
    
    def visit_FuncDef(self, node):
        def agg_res(node, args):
            return node.lvalue.name
        av = AssignmentVisitor(func=agg_res)
        av.visit(node)
        self.assigned_params = av.result
        self.current_scope = node.decl.name
        if hasattr(node.body, "block_items") and \
                node.body.block_items is not None:
            node.body.block_items = self.process_block_items(self.current_scope,
                                                             node.body.block_items)


class Release2Transform(c_ast.NodeVisitor):
    """ Rule 2: call "RELEASE(x)" before reuse the variable name x
                as a computation variable.
    """
    def __init__(self, scope_table):
        self.scope_table = scope_table
        self.local_vars = []
        self.current_scope = None

    def process_compound(self, node, loop=False, conds=[], prior_use={}):
        # conds: [(id, type, init)]
        i = 0
        l = len(node.block_items)
        while i < l:
            itm = node.block_items[i]
            if isinstance(itm, c_ast.Assignment) \
                and (isinstance(itm.lvalue, c_ast.ID) or
                     isinstance(itm.lvalue, c_ast.Decl)) \
                and itm.lvalue.name in self.local_vars:
                if itm.lvalue.name in self.params and prior_use.get(itm.lvalue.name, False):
                    release_call = new_fcall(RELEASE_fcall, [itm.lvalue.name])
                    node.block_items.insert(i, release_call)
                    i += 1
                    l += 1
                elif itm.lvalue.name not in self.params:
                    release_call = new_fcall(RELEASE_fcall, [itm.lvalue.name])
                    node.block_items.insert(i, release_call)
                    i += 1
                    l += 1
                else:
                    if loop:
                        if len(conds) > 1:
                            raise Exception("Multiple loop conditions not handled")
                        release_call = new_fcall(RELEASE_fcall, [itm.lvalue.name])
                        cond = None
                        for cnd in conds:
                            # cnd: (lhs, rhs, type)
                            cond = new_condop(cnd[2], "!=", cnd[0], cnd[1])
                        guard = new_if(cond, release_call, None)
                        node.block_items.insert(i, guard)
                        i += 1
                        l += 1
                    prior_use[itm.lvalue.name] = True
            elif isinstance(itm, c_ast.Assignment) \
                and isinstance(itm.lvalue, c_ast.ArrayRef) \
                and itm.lvalue.name.name in self.local_vars:
                if True:
                    release_call = new_fcall(RELEASE_fcall, [itm.lvalue])
                    node.block_items.insert(i, release_call)
                    i += 1
                    l += 1
                else:
                    if loop:
                        raise Exception("ArrayRef in loop Not handled")
                    prior_use[itm.lvalue.name] = True
            elif isinstance(itm, c_ast.Decl) \
                and itm.type.__class__ == c_ast.TypeDecl \
                and join_type(itm.type.type.names) in POOL_types \
                and hasattr(itm, "init") \
                and itm.init.__class__ == c_ast.FuncCall:
                prior_use[itm.name] = True
            elif isinstance(itm, c_ast.For):
                conds = []
                if PROCESS_LOOP_RELEASE:
                    if isinstance(itm.init, c_ast.Assignment):
                        typ = "int"
                        if isinstance(itm.init.rvalue, c_ast.Constant):
                            # WARNING: no type inference for this loop condition
                            typ = "int"
                        else:
                            raise Exception("For init condition rhs is not Constant.")
                        if isinstance(itm.init.lvalue, c_ast.ID):
                            conds.append((new_var(itm.init.lvalue.name), itm.init.rvalue.value, typ))
                        else:
                            raise Exception("Non-ID lvalue!")
                    elif isinstance(itm.init, c_ast.DeclList):
                        for decl in itm.init.decls:
                            typ = "int"
                            if isinstance(decl.init, c_ast.Constant):
                                typ = decl.init.type
                            else:
                                raise Exception("For init condition rhs is not Constant.")
                            conds.append((new_var(decl.name), decl.init, typ))
                if not isinstance(itm.stmt, c_ast.Compound):
                    itm.stmt = c_ast.Compound([itm.stmt])
                self.local_vars = [x for x in self.local_vars if x not in self.params]
                self.local_vars.extend(ids_of_type2(self.scope_table,
                                                    self.current_scope, 
                                                    POOL_types))
                self.local_vars.extend(ids_of_type3(self.scope_table,
                                                    self.current_scope, 
                                                    POOL_types))
                self.process_compound(itm.stmt,
                                        loop=PROCESS_LOOP_RELEASE,
                                        conds=conds,
                                        prior_use=prior_use)
            elif isinstance(itm, c_ast.While):
                conds = []
                if PROCESS_LOOP_RELEASE:
                    if isinstance(itm.cond, c_ast.BinaryOp):
                        lhs = itm.cond.left.name
                        decl = [x for x in self.scope_table.get(self.current_scope, [])
                                if x[0] == lhs][0]
                        if decl[2]:
                            conds.append((new_var(decl[0]), decl[2], decl[1]))
                    else:
                        raise Exception("Unhandled while condition class.")
                if isinstance(itm.stmt, c_ast.Compound):
                    self.local_vars = [x for x in self.local_vars if x not in self.params]
                    self.local_vars.extend(ids_of_type2(self.scope_table, 
                                                       self.current_scope, 
                                                       POOL_types))
                    self.process_compound(itm.stmt,
                                          loop=PROCESS_LOOP_RELEASE,
                                          conds=conds,
                                          prior_use=prior_use)
            elif isinstance(itm, c_ast.If):
                self.local_vars = [x for x in self.local_vars if x not in self.params]
                self.local_vars.extend(ids_of_type2(self.scope_table, 
                                                       self.current_scope, 
                                                       POOL_types))
                if isinstance(itm.iftrue, c_ast.Compound):
                    self.process_compound(itm.iftrue)
                if isinstance(itm.iffalse, c_ast.Compound):
                    self.process_compound(itm.iffalse)
            i += 1

    def visit_FuncDef(self, node):
        self.current_scope = node.decl.name
        self.local_vars, self.params = ids_of_type(self.scope_table, self.current_scope, POOL_types)
        self.local_vars.extend(self.params)
        if hasattr(node.body, "block_items") and \
                node.body.block_items is not None:
            self.process_compound(node.body, prior_use={})


class Release3Transform(c_ast.NodeVisitor):
    """ Rule 4: use a fresh variable name once a input variable
                is reassigned with a value.
    """
    def __init__(self, scope_table):
        self.scope_table = scope_table
        self.local_vars = []
        self.ctr = 0
        self.rename = {}

    def process_compound(self, node):
        i = 0
        l = len(node.block_items)
        def rename(ident, args):
            table = args[0]
            i = args[1]
            if table.get(ident.name, False) and i > table[ident.name][1]:
                ident.name = table[ident.name][0]
        while i < l:
            itm = node.block_items[i]
            if itm.__class__ == c_ast.Assignment \
                and itm.rvalue.__class__ == c_ast.FuncCall \
                and (itm.lvalue.__class__ == c_ast.ID \
                or itm.lvalue.__class__ == c_ast.Decl) \
                and itm.lvalue.name in self.local_vars:
                tmp_var = new_ivar("__tmp__a"+str(self.ctr))
                self.rename[itm.lvalue.name] = (tmp_var.name, i)
                # itm.lvalue = tmp_var
                tmp_var.init = itm.rvalue
                node.block_items[i] = tmp_var
            elif itm.__class__ == c_ast.For:
                if itm.stmt is not None:
                    if itm.stmt.__class__.__name__ == "Compound":
                        self.process_compound(itm.stmt)
            else:
                iv = IDVisitor(func=rename, args=[self.rename, i])
                iv.visit(itm)
            i += 1

    def visit_FuncDef(self, node):
        current_scope = node.decl.name
        self.local_vars = [x[0] for x in self.scope_table.get(current_scope+":Param", [])
                           if x[1] in POOL_types]
        if hasattr(node.body, "block_items") and \
                node.body.block_items is not None:
            self.process_compound(node.body)


class CopyTransform(c_ast.NodeVisitor):
    """ Add COPY call if node is:
            - assignment where type of lhs is bit
            - decl of type bit w/init
    """
    def __init__(self, scope_table):
        self.scope_table = scope_table

    def copy_rewrite(self, node, args):
        local_vars = args[0]
        if node.__class__ == c_ast.Assignment:
            if node.lvalue.__class__ == c_ast.ArrayRef:
                if node.lvalue.name.name in local_vars:
                    if node.rvalue.__class__ == c_ast.ID:
                        node.rvalue = new_fcall(COPY_fcall, [node.rvalue.name])
                    elif node.rvalue.__class__ == c_ast.ArrayRef:
                        node.rvalue = new_fcall(COPY_fcall, [node.rvalue])
            elif node.lvalue.__class__ == c_ast.ID:
                if node.lvalue.name in local_vars:
                    if node.rvalue.__class__ == c_ast.ID:
                        node.rvalue = new_fcall(COPY_fcall, [node.rvalue.name])
                    elif node.rvalue.__class__ == c_ast.ArrayRef:
                        node.rvalue = new_fcall(COPY_fcall, [node.rvalue])
        elif node.__class__ == c_ast.Decl:
            if node.type.__class__ == c_ast.TypeDecl \
               and join_type(node.type.type.names) in POOL_types \
               and hasattr(node, "init") and node.init is not None \
               and node.init.__class__ == c_ast.ID:
                node.init = new_fcall(COPY_fcall, [node.init.name])
        else:
            raise Exception("Copy transform only defined for \
                             assignment and initalized decl")

    def visit_FuncDef(self, node):
        local_vars = [x[0] for x in self.scope_table.get(node.decl.name, [])
                      if x[1] in POOL_types]
        local_vars.extend([x[0] for x in self.scope_table.get(node.decl.name+":Param", [])
                           if x[1] in POOL_types])
        local_vars.extend([x[0] for x in self.scope_table.get(node.decl.name+":ParamPtr", [])
                           if x[1] in POOL_types])
        av = AssignmentVisitor(func=self.copy_rewrite, args=[local_vars])
        dv = VarDeclVisitor(func=self.copy_rewrite, args=[local_vars])
        av.visit(node)
        dv.visit(node)


class NewVarTransform(c_ast.NodeVisitor):
    """ Add NewVar to decl of type bit where rhs is None """
    def visit_Decl(self, node):
        if isinstance(node.type, c_ast.TypeDecl) \
            and join_type(node.type.type.names) in POOL_types \
            and hasattr(node, "init") and node.init is None:
            if not (hasattr(node, 'storage') and 'extern' in node.storage):
                node.init = new_fcall(NEWVAR_fcall, [])
        if isinstance(node.type, c_ast.ArrayDecl) \
            and join_type(node.type.type.type.names) in POOL_types \
            and hasattr(node, "init") and node.init is None:
            if not (hasattr(node, 'storage') and 'extern' in node.storage):
                typ = join_type(node.type.type.type.names)
                var_name = typ + " " + node.name + "[" + str(node.type.dim.value) + "]; " + NEWARR_fcall + "(" + node.name + ", " + str(node.type.dim.value) + ")"
                node.type = new_var(var_name)
                # node.type.type.declname = node.name + "; " + NEWARR_fcall + "(" + node.name + ", " + str(node.type.dim) + ")"
                # node.init = new_fcall(NEWARR_fcall, [node.type.dim])


class RewriteBitFuncs(c_ast.NodeVisitor):
    def visit_FuncCall(self, node):
        if node.name.name == "XOR":
            node.name = new_var(XOR_fcall)
        if node.name.name == 'AND':
            node.name = new_var(AND_fcall)


def process_c(ast):
    """ Helper method to trigger the calling of
        the root visitors.
    """
    ThreeACTransform().visit(ast)
    genST = GenerateScopeTable()
    genST.visit(ast)
    NewVarTransform().visit(ast)
    CopyTransform(genST.scope_table).visit(ast)
    Release1Transform(genST.scope_table).visit(ast)
    Release2Transform(genST.scope_table).visit(ast)
    # Release3Transform(genST.scope_table).visit(ast)
    RewriteBitFuncs().visit(ast)

def generate_ast(filename):
    """ Generate the ast from the cleaned source."""
    src = ""
    with open(filename, "r") as src_file:
        for line in src_file.readlines():
            src += line
    ast = parse_file(filename, use_cpp=True)
    return ast

def generate_c(filename, ast):
    out_string = ""
    generator = c_generator.CGenerator()
    out_string += generator.visit(ast)
    # print out_string
    with open(filename, "w") as out_file:
        out_file.write(out_string)

def main(argv):
    if argv == []:
        print "Please supply files to parse!"
        exit(-1)
    for filename in argv:
        print "-------------TRAVERSE_AST----------------"
        # Traverse the AST for transformations
        ast = generate_ast(filename)
        # ast.show()
        print "--------------PROCESS_C------------------"
        process_c(ast)
        print "-------------OUTPUT_TRANSF---------------"
        # Output the transformed C code
        filename_3 = filename.split(".")[0] + "__3ac.c"
        generate_c(filename_3, ast)

if __name__ == "__main__":
    main(sys.argv[1:])
