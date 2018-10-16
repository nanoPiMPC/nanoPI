import re, sys


def read_file(name):
    lines = []
    with open(name, 'r') as f:
        lines = f.readlines()
    return lines

def tokenize(lines):
    tokens = []
    for line in lines:
        tokens.extend(
            [x.strip() for x 
             in line.split(" ") 
             if x != ''])
    return tokens

class Frame(object):
    def __init__(self):
        self.start_tok = 0
        self.up = None
        self.down = []
        self.code = []
        self.decls = []
        self.var_list = []
    def __repr__(self):
        out_str = \
            "~~~~~~~Frame~ " + \
            str(self.start_tok) + " ~~~~~~~\n" + \
            str(self.code) + "\n" + \
            "     --- Decls ----     \n" + \
            str(self.decls) + "\n" + \
            "     --- Vars  ----     \n" + \
            str(self.var_list) + "\n" + \
            "~~~~~~~~~~~~~~~~~~~~~~~~\n"
        return out_str

def frameize(tokens):
    frames = []
    current = Frame()
    stack = []
    ctr_stack = [0]
    for token in tokens:
        current.code.append(token)
        ctr_stack[-1] += 1
        if token == '{':
            tmp = Frame()
            tmp.up = current
            tmp.start_tok = ctr_stack[-1]
            current.down.append(tmp)
            stack.append(current)
            current = tmp
            ctr_stack.append(0)
        elif token == '}':
            frames.append(current)
            current = stack.pop()
            ctr_stack.pop()
    frames.append(current)
    return frames

def extract_vars(frame):
    keywords = ['return', 'while', 'if', 'else', 'break', 'for']
    decl_words = ['int', 'char', 'float', 'void', 'double']
    symbols = ['(', '%', '<', '>', '#', '{', '}']
    var_list = []
    for i, token in enumerate(frame.code):
        cont = True
        if token in keywords:
            cont = False
        for symbol in symbols:
            if symbol in list(token):
                cont = False
        if cont:
            m = re.search('([a-zA-Z_][a-zA-Z0-9_]*)', token)
            if m:
                var_list.append((m.group(0), i))
    decls = []
    vars_clean = []
    i = 0
    while i < len(var_list):
        if var_list[i][0] in decl_words:
            if i + 1 < len(var_list) and \
            var_list[i + 1][0] not in decl_words:
                decls.append(var_list[i + 1])
            i += 1
        else:
            vars_clean.append(var_list[i])
        i += 1
    return decls, vars_clean

var_ctr = 0
def rename(root, table):
    global var_ctr
    decls, var_list = extract_vars(root)
    appended = {}
    for decl in decls:
        var_ctr += 1
        if not table.get(decl[0], None):
            table[decl[0]] = []
        table[decl[0]].append("var_" + str(var_ctr))
        appended[decl[0]] = True
    for i, var in enumerate(var_list):
        if table.get(var[0], None):
            var_list[i] = (var[0], table[var[0]][-1], var[1])
    for i, decl in enumerate(decls):
        decls[i] = (decl[0], table[decl[0]][-1], decl[1])
    root.decls = decls
    root.var_list = var_list
    for decl in root.decls:
        root.code[decl[2]] = \
            root.code[decl[2]].replace(decl[0], decl[1])
    for var in root.var_list:
        if len(var) == 3:
            root.code[var[2]] = \
                root.code[var[2]].replace(var[0], var[1])
    for i, frame in enumerate(root.down):
        rename(frame, table)
    for decl, added in appended.items():
        if added is True:
            table[decl].pop()
    return appended

def release_and_copy(root, table):
    decls, var_list = extract_vars(root)
    print var_list
    root.decls = decls
    root.var_list = var_list
    def last_call(var_name):
        last = None
        for var, i in var_list:
            if var == var_name:
                last = i
        return last
    for var, i in var_list:
        indx = last_call(var)
        root.code[indx] = root.code[indx] + " RELEASE(" + var + ");"
    for frame in root.down:
        release_and_copy(frame, table)

def output_code(root):
    tokens = []
    tokens.extend(root.code)
    offset = 0
    for frame in root.down:
        print tokens
        t1 = tokens[:frame.start_tok+offset]
        print t1
        t2 = tokens[frame.start_tok+offset:]
        print t2
        ext = output_code(frame)
        print ext
        t1.extend(ext)
        offset += len(ext)
        print offset
        t1.extend(t2)
        tokens = t1
    return tokens

def print_code(code_list):
    out_str = ""
    tc = 0
    for item in code_list:
        if item == "{":
            tc += 1
            out_str += item + "\n"
            out_str += "\t"*tc
        elif item == "}":
            out_str = out_str[:-1]
            out_str += item + "\n"
            tc -= 1
            out_str += "\t"*tc
        elif ">" in item:
            out_str += item + "\n"
        elif ";" in item:
            out_str += item + "\n"
            out_str += "\t"*tc
        elif item != '':
            out_str += item + " "
    print out_str

def main(filename):
    lines = read_file(filename)
    tokens = tokenize(lines)
    frames = frameize(tokens)
    root = frames[-1]
    # Uncomment to handle unique renaming
    # rename(root, {})
    release_and_copy(root, {})
    # for frame in frames:
    #    print frame
    print_code(output_code(root))

if __name__ == "__main__":
    argv = sys.argv[1:]
    if argv == []:
        print "Please supply files to parse!"
        exit(-1)
    else:
        for filename in argv:
            main(filename)
