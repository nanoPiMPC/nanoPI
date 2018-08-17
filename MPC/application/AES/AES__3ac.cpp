#ifndef Simulator
#include "Stage.hpp"
#else
#include "BackendSimulator.hpp"
#endif
#define Scale 100
#ifdef B3
#define MainPoolSize 479000
#define MainStageSize 1280*Scale
#define MainBuffer 1280*Scale
#define MainWireArraySize 65000*Scale
#define MainBucketSize 3
#endif
Index Zero,One;
void GFINV(Index src[])
{
    Index T[27];
    __pool__NewArray(T,27);
    Index M[63];
    __pool__NewArray(M,63);
    Index L[30];
    __pool__NewArray(L,30);
    Index __tmp__4 = __pool__XOR(src[0], src[3]);
    __pool__RELEASE(T[0]);
    T[0] = __pool__COPY(__tmp__4);
    Index __tmp__5 = __pool__XOR(src[0], src[5]);
    __pool__RELEASE(T[1]);
    T[1] = __pool__COPY(__tmp__5);
    Index __tmp__6 = __pool__XOR(src[0], src[6]);
    __pool__RELEASE(T[2]);
    T[2] = __pool__COPY(__tmp__6);
    Index __tmp__7 = __pool__XOR(src[3], src[5]);
    __pool__RELEASE(T[3]);
    T[3] = __pool__COPY(__tmp__7);
    Index __tmp__8 = __pool__XOR(src[4], src[6]);
    __pool__RELEASE(T[4]);
    T[4] = __pool__COPY(__tmp__8);
    Index __tmp__9 = __pool__XOR(T[0], T[4]);
    __pool__RELEASE(T[5]);
    T[5] = __pool__COPY(__tmp__9);
    Index __tmp__10 = __pool__XOR(src[1], src[2]);
    __pool__RELEASE(T[6]);
    T[6] = __pool__COPY(__tmp__10);
    Index __tmp__11 = __pool__XOR(src[7], T[5]);
    __pool__RELEASE(T[7]);
    T[7] = __pool__COPY(__tmp__11);
    Index __tmp__12 = __pool__XOR(src[7], T[6]);
    __pool__RELEASE(T[8]);
    T[8] = __pool__COPY(__tmp__12);
    Index __tmp__13 = __pool__XOR(T[5], T[6]);
    __pool__RELEASE(T[9]);
    T[9] = __pool__COPY(__tmp__13);
    Index __tmp__14 = __pool__XOR(src[1], src[5]);
    __pool__RELEASE(T[10]);
    T[10] = __pool__COPY(__tmp__14);
    Index __tmp__15 = __pool__XOR(src[2], src[5]);
    __pool__RELEASE(T[11]);
    T[11] = __pool__COPY(__tmp__15);
    Index __tmp__16 = __pool__XOR(T[2], T[3]);
    __pool__RELEASE(T[12]);
    T[12] = __pool__COPY(__tmp__16);
    Index __tmp__17 = __pool__XOR(T[5], T[10]);
    __pool__RELEASE(T[13]);
    T[13] = __pool__COPY(__tmp__17);
    Index __tmp__18 = __pool__XOR(T[4], T[10]);
    __pool__RELEASE(T[14]);
    T[14] = __pool__COPY(__tmp__18);
    Index __tmp__19 = __pool__XOR(T[4], T[11]);
    __pool__RELEASE(T[15]);
    T[15] = __pool__COPY(__tmp__19);
    Index __tmp__20 = __pool__XOR(T[8], T[15]);
    __pool__RELEASE(T[16]);
    T[16] = __pool__COPY(__tmp__20);
    Index __tmp__21 = __pool__XOR(src[3], src[7]);
    __pool__RELEASE(T[17]);
    T[17] = __pool__COPY(__tmp__21);
    Index __tmp__22 = __pool__XOR(T[6], T[17]);
    __pool__RELEASE(T[18]);
    T[18] = __pool__COPY(__tmp__22);
    Index __tmp__23 = __pool__XOR(T[0], T[18]);
    __pool__RELEASE(T[19]);
    T[19] = __pool__COPY(__tmp__23);
    Index __tmp__24 = __pool__XOR(src[6], src[7]);
    __pool__RELEASE(T[20]);
    T[20] = __pool__COPY(__tmp__24);
    Index __tmp__25 = __pool__XOR(T[6], T[20]);
    __pool__RELEASE(T[21]);
    T[21] = __pool__COPY(__tmp__25);
    Index __tmp__26 = __pool__XOR(T[1], T[21]);
    __pool__RELEASE(T[22]);
    T[22] = __pool__COPY(__tmp__26);
    Index __tmp__27 = __pool__XOR(T[1], T[9]);
    __pool__RELEASE(T[23]);
    T[23] = __pool__COPY(__tmp__27);
    Index __tmp__28 = __pool__XOR(T[19], T[16]);
    __pool__RELEASE(T[24]);
    T[24] = __pool__COPY(__tmp__28);
    Index __tmp__29 = __pool__XOR(T[2], T[15]);
    __pool__RELEASE(T[25]);
    T[25] = __pool__COPY(__tmp__29);
    Index __tmp__30 = __pool__XOR(T[0], T[11]);
    __pool__RELEASE(T[26]);
    T[26] = __pool__COPY(__tmp__30);
    Index __tmp__31 = __pool__AND(T[5], T[12]);
    __pool__RELEASE(M[0]);
    M[0] = __pool__COPY(__tmp__31);
    Index __tmp__32 = __pool__AND(T[7], T[22]);
    __pool__RELEASE(M[1]);
    M[1] = __pool__COPY(__tmp__32);
    Index __tmp__33 = __pool__AND(src[7], T[18]);
    __pool__RELEASE(M[3]);
    M[3] = __pool__COPY(__tmp__33);
    Index __tmp__34 = __pool__AND(T[2], T[15]);
    __pool__RELEASE(M[5]);
    M[5] = __pool__COPY(__tmp__34);
    Index __tmp__35 = __pool__AND(T[8], T[21]);
    __pool__RELEASE(M[6]);
    M[6] = __pool__COPY(__tmp__35);
    Index __tmp__36 = __pool__AND(T[16], T[19]);
    __pool__RELEASE(M[8]);
    M[8] = __pool__COPY(__tmp__36);
    Index __tmp__37 = __pool__AND(T[0], T[14]);
    __pool__RELEASE(M[10]);
    M[10] = __pool__COPY(__tmp__37);
    Index __tmp__38 = __pool__AND(T[3], T[26]);
    __pool__RELEASE(M[11]);
    M[11] = __pool__COPY(__tmp__38);
    Index __tmp__39 = __pool__AND(T[1], T[9]);
    __pool__RELEASE(M[13]);
    M[13] = __pool__COPY(__tmp__39);
    __pool__RELEASE(M[2]);
    M[2] = __pool__COPY(T[13]);
    __pool__RELEASE(M[7]);
    M[7] = __pool__COPY(T[24]);
    __pool__RELEASE(M[45]);
    M[45] = __pool__COPY(T[5]);
    __pool__RELEASE(M[46]);
    M[46] = __pool__COPY(T[7]);
    __pool__RELEASE(M[47]);
    M[47] = __pool__COPY(src[7]);
    __pool__RELEASE(M[48]);
    M[48] = __pool__COPY(T[14]);
    __pool__RELEASE(M[49]);
    M[49] = __pool__COPY(T[8]);
    __pool__RELEASE(M[50]);
    M[50] = __pool__COPY(T[16]);
    __pool__RELEASE(M[51]);
    M[51] = __pool__COPY(T[14]);
    __pool__RELEASE(M[52]);
    M[52] = __pool__COPY(T[26]);
    __pool__RELEASE(M[53]);
    M[53] = __pool__COPY(T[9]);
    __pool__RELEASE(M[54]);
    M[54] = __pool__COPY(T[12]);
    __pool__RELEASE(M[55]);
    M[55] = __pool__COPY(T[22]);
    __pool__RELEASE(M[56]);
    M[56] = __pool__COPY(T[18]);
    __pool__RELEASE(M[57]);
    M[57] = __pool__COPY(T[2]);
    __pool__RELEASE(M[58]);
    M[58] = __pool__COPY(T[21]);
    __pool__RELEASE(M[59]);
    M[59] = __pool__COPY(T[19]);
    __pool__RELEASE(M[60]);
    M[60] = __pool__COPY(T[0]);
    __pool__RELEASE(M[61]);
    M[61] = __pool__COPY(T[3]);
    __pool__RELEASE(M[62]);
    M[62] = __pool__COPY(T[1]);
    Index __tmp__60 = __pool__XOR(M[2], M[0]);
    __pool__RELEASE(M[2]);
    M[2] = __pool__COPY(__tmp__60);
    Index __tmp__61 = __pool__XOR(M[3], M[0]);
    __pool__RELEASE(M[4]);
    M[4] = __pool__COPY(__tmp__61);
    Index __tmp__62 = __pool__XOR(M[7], M[5]);
    __pool__RELEASE(M[7]);
    M[7] = __pool__COPY(__tmp__62);
    Index __tmp__63 = __pool__XOR(M[8], M[5]);
    __pool__RELEASE(M[9]);
    M[9] = __pool__COPY(__tmp__63);
    Index __tmp__64 = __pool__XOR(M[10], M[11]);
    __pool__RELEASE(M[12]);
    M[12] = __pool__COPY(__tmp__64);
    Index __tmp__65 = __pool__XOR(M[10], M[13]);
    __pool__RELEASE(M[14]);
    M[14] = __pool__COPY(__tmp__65);
    Index __tmp__66 = __pool__XOR(M[2], M[1]);
    __pool__RELEASE(M[15]);
    M[15] = __pool__COPY(__tmp__66);
    Index __tmp__67 = __pool__XOR(M[4], M[15]);
    __pool__RELEASE(M[16]);
    M[16] = __pool__COPY(__tmp__67);
    Index __tmp__68 = __pool__XOR(M[6], M[7]);
    __pool__RELEASE(M[17]);
    M[17] = __pool__COPY(__tmp__68);
    Index __tmp__69 = __pool__XOR(M[9], M[14]);
    __pool__RELEASE(M[18]);
    M[18] = __pool__COPY(__tmp__69);
    Index __tmp__70 = __pool__XOR(M[15], M[12]);
    __pool__RELEASE(M[19]);
    M[19] = __pool__COPY(__tmp__70);
    Index __tmp__71 = __pool__XOR(M[16], M[14]);
    __pool__RELEASE(M[20]);
    M[20] = __pool__COPY(__tmp__71);
    Index __tmp__72 = __pool__XOR(M[12], M[17]);
    __pool__RELEASE(M[21]);
    M[21] = __pool__COPY(__tmp__72);
    Index __tmp__73 = __pool__XOR(M[18], M[21]);
    __pool__RELEASE(M[22]);
    M[22] = __pool__COPY(__tmp__73);
    Index __tmp__74 = __pool__XOR(M[21], M[22]);
    __pool__RELEASE(M[23]);
    M[23] = __pool__COPY(__tmp__74);
    Index __tmp__75 = __pool__XOR(M[19], M[20]);
    __pool__RELEASE(M[26]);
    M[26] = __pool__COPY(__tmp__75);
    Index __tmp__76 = __pool__AND(M[19], M[21]);
    __pool__RELEASE(M[24]);
    M[24] = __pool__COPY(__tmp__76);
    Index __tmp__77 = __pool__AND(M[19], M[22]);
    __pool__RELEASE(M[30]);
    M[30] = __pool__COPY(__tmp__77);
    Index __tmp__78 = __pool__AND(M[20], M[21]);
    __pool__RELEASE(M[33]);
    M[33] = __pool__COPY(__tmp__78);
    Index __tmp__79 = __pool__XOR(M[20], M[24]);
    __pool__RELEASE(M[25]);
    M[25] = __pool__COPY(__tmp__79);
    Index __tmp__80 = __pool__XOR(M[22], M[24]);
    __pool__RELEASE(M[27]);
    M[27] = __pool__COPY(__tmp__80);
    Index __tmp__81 = __pool__XOR(M[26], M[24]);
    __pool__RELEASE(M[32]);
    M[32] = __pool__COPY(__tmp__81);
    Index __tmp__82 = __pool__XOR(M[23], M[24]);
    __pool__RELEASE(M[35]);
    M[35] = __pool__COPY(__tmp__82);
    Index __tmp__83 = __pool__AND(M[26], M[27]);
    __pool__RELEASE(M[28]);
    M[28] = __pool__COPY(__tmp__83);
    Index __tmp__84 = __pool__AND(M[23], M[25]);
    __pool__RELEASE(M[29]);
    M[29] = __pool__COPY(__tmp__84);
    Index __tmp__85 = __pool__AND(M[26], M[30]);
    __pool__RELEASE(M[31]);
    M[31] = __pool__COPY(__tmp__85);
    Index __tmp__86 = __pool__AND(M[23], M[33]);
    __pool__RELEASE(M[34]);
    M[34] = __pool__COPY(__tmp__86);
    Index __tmp__87 = __pool__XOR(M[20], M[28]);
    __pool__RELEASE(M[36]);
    M[36] = __pool__COPY(__tmp__87);
    Index __tmp__88 = __pool__XOR(M[31], M[32]);
    __pool__RELEASE(M[37]);
    M[37] = __pool__COPY(__tmp__88);
    Index __tmp__89 = __pool__XOR(M[22], M[29]);
    __pool__RELEASE(M[38]);
    M[38] = __pool__COPY(__tmp__89);
    Index __tmp__90 = __pool__XOR(M[34], M[35]);
    __pool__RELEASE(M[39]);
    M[39] = __pool__COPY(__tmp__90);
    Index __tmp__91 = __pool__XOR(M[37], M[39]);
    __pool__RELEASE(M[40]);
    M[40] = __pool__COPY(__tmp__91);
    Index __tmp__92 = __pool__XOR(M[36], M[38]);
    __pool__RELEASE(M[41]);
    M[41] = __pool__COPY(__tmp__92);
    Index __tmp__93 = __pool__XOR(M[36], M[37]);
    __pool__RELEASE(M[42]);
    M[42] = __pool__COPY(__tmp__93);
    Index __tmp__94 = __pool__XOR(M[38], M[39]);
    __pool__RELEASE(M[43]);
    M[43] = __pool__COPY(__tmp__94);
    Index __tmp__95 = __pool__XOR(M[41], M[30]);
    __pool__RELEASE(M[44]);
    M[44] = __pool__COPY(__tmp__95);
    Index __tmp__96 = __pool__AND(M[45], M[43]);
    __pool__RELEASE(M[45]);
    M[45] = __pool__COPY(__tmp__96);
    Index __tmp__97 = __pool__AND(M[46], M[39]);
    __pool__RELEASE(M[46]);
    M[46] = __pool__COPY(__tmp__97);
    Index __tmp__98 = __pool__AND(M[47], M[38]);
    __pool__RELEASE(M[47]);
    M[47] = __pool__COPY(__tmp__98);
    Index __tmp__99 = __pool__AND(M[48], M[42]);
    __pool__RELEASE(M[48]);
    M[48] = __pool__COPY(__tmp__99);
    Index __tmp__100 = __pool__AND(M[49], M[37]);
    __pool__RELEASE(M[49]);
    M[49] = __pool__COPY(__tmp__100);
    Index __tmp__101 = __pool__AND(M[50], M[36]);
    __pool__RELEASE(M[50]);
    M[50] = __pool__COPY(__tmp__101);
    Index __tmp__102 = __pool__AND(M[51], M[41]);
    __pool__RELEASE(M[51]);
    M[51] = __pool__COPY(__tmp__102);
    Index __tmp__103 = __pool__AND(M[52], M[44]);
    __pool__RELEASE(M[52]);
    M[52] = __pool__COPY(__tmp__103);
    Index __tmp__104 = __pool__AND(M[53], M[40]);
    __pool__RELEASE(M[53]);
    M[53] = __pool__COPY(__tmp__104);
    Index __tmp__105 = __pool__AND(M[54], M[43]);
    __pool__RELEASE(M[54]);
    M[54] = __pool__COPY(__tmp__105);
    Index __tmp__106 = __pool__AND(M[55], M[39]);
    __pool__RELEASE(M[55]);
    M[55] = __pool__COPY(__tmp__106);
    Index __tmp__107 = __pool__AND(M[56], M[38]);
    __pool__RELEASE(M[56]);
    M[56] = __pool__COPY(__tmp__107);
    Index __tmp__108 = __pool__AND(M[57], M[42]);
    __pool__RELEASE(M[57]);
    M[57] = __pool__COPY(__tmp__108);
    Index __tmp__109 = __pool__AND(M[58], M[37]);
    __pool__RELEASE(M[58]);
    M[58] = __pool__COPY(__tmp__109);
    Index __tmp__110 = __pool__AND(M[59], M[36]);
    __pool__RELEASE(M[59]);
    M[59] = __pool__COPY(__tmp__110);
    Index __tmp__111 = __pool__AND(M[60], M[41]);
    __pool__RELEASE(M[60]);
    M[60] = __pool__COPY(__tmp__111);
    Index __tmp__112 = __pool__AND(M[61], M[44]);
    __pool__RELEASE(M[61]);
    M[61] = __pool__COPY(__tmp__112);
    Index __tmp__113 = __pool__AND(M[62], M[40]);
    __pool__RELEASE(M[62]);
    M[62] = __pool__COPY(__tmp__113);
    Index __tmp__114 = __pool__XOR(M[60], M[61]);
    __pool__RELEASE(L[0]);
    L[0] = __pool__COPY(__tmp__114);
    Index __tmp__115 = __pool__XOR(M[49], M[55]);
    __pool__RELEASE(L[1]);
    L[1] = __pool__COPY(__tmp__115);
    Index __tmp__116 = __pool__XOR(M[45], M[47]);
    __pool__RELEASE(L[2]);
    L[2] = __pool__COPY(__tmp__116);
    Index __tmp__117 = __pool__XOR(M[46], M[54]);
    __pool__RELEASE(L[3]);
    L[3] = __pool__COPY(__tmp__117);
    Index __tmp__118 = __pool__XOR(M[53], M[57]);
    __pool__RELEASE(L[4]);
    L[4] = __pool__COPY(__tmp__118);
    Index __tmp__119 = __pool__XOR(M[48], M[60]);
    __pool__RELEASE(L[5]);
    L[5] = __pool__COPY(__tmp__119);
    Index __tmp__120 = __pool__XOR(M[61], L[5]);
    __pool__RELEASE(L[6]);
    L[6] = __pool__COPY(__tmp__120);
    Index __tmp__121 = __pool__XOR(M[45], L[3]);
    __pool__RELEASE(L[7]);
    L[7] = __pool__COPY(__tmp__121);
    Index __tmp__122 = __pool__XOR(M[50], M[58]);
    __pool__RELEASE(L[8]);
    L[8] = __pool__COPY(__tmp__122);
    Index __tmp__123 = __pool__XOR(M[51], M[52]);
    __pool__RELEASE(L[9]);
    L[9] = __pool__COPY(__tmp__123);
    Index __tmp__124 = __pool__XOR(M[52], L[4]);
    __pool__RELEASE(L[10]);
    L[10] = __pool__COPY(__tmp__124);
    Index __tmp__125 = __pool__XOR(M[59], L[2]);
    __pool__RELEASE(L[11]);
    L[11] = __pool__COPY(__tmp__125);
    Index __tmp__126 = __pool__XOR(M[47], M[50]);
    __pool__RELEASE(L[12]);
    L[12] = __pool__COPY(__tmp__126);
    Index __tmp__127 = __pool__XOR(M[49], L[0]);
    __pool__RELEASE(L[13]);
    L[13] = __pool__COPY(__tmp__127);
    Index __tmp__128 = __pool__XOR(M[51], M[60]);
    __pool__RELEASE(L[14]);
    L[14] = __pool__COPY(__tmp__128);
    Index __tmp__129 = __pool__XOR(M[54], L[1]);
    __pool__RELEASE(L[15]);
    L[15] = __pool__COPY(__tmp__129);
    Index __tmp__130 = __pool__XOR(M[55], L[0]);
    __pool__RELEASE(L[16]);
    L[16] = __pool__COPY(__tmp__130);
    Index __tmp__131 = __pool__XOR(M[56], L[1]);
    __pool__RELEASE(L[17]);
    L[17] = __pool__COPY(__tmp__131);
    Index __tmp__132 = __pool__XOR(M[57], L[8]);
    __pool__RELEASE(L[18]);
    L[18] = __pool__COPY(__tmp__132);
    Index __tmp__133 = __pool__XOR(M[62], L[4]);
    __pool__RELEASE(L[19]);
    L[19] = __pool__COPY(__tmp__133);
    Index __tmp__134 = __pool__XOR(L[0], L[1]);
    __pool__RELEASE(L[20]);
    L[20] = __pool__COPY(__tmp__134);
    Index __tmp__135 = __pool__XOR(L[1], L[7]);
    __pool__RELEASE(L[21]);
    L[21] = __pool__COPY(__tmp__135);
    Index __tmp__136 = __pool__XOR(L[3], L[12]);
    __pool__RELEASE(L[22]);
    L[22] = __pool__COPY(__tmp__136);
    Index __tmp__137 = __pool__XOR(L[18], L[2]);
    __pool__RELEASE(L[23]);
    L[23] = __pool__COPY(__tmp__137);
    Index __tmp__138 = __pool__XOR(L[15], L[9]);
    __pool__RELEASE(L[24]);
    L[24] = __pool__COPY(__tmp__138);
    Index __tmp__139 = __pool__XOR(L[6], L[10]);
    __pool__RELEASE(L[25]);
    L[25] = __pool__COPY(__tmp__139);
    Index __tmp__140 = __pool__XOR(L[7], L[9]);
    __pool__RELEASE(L[26]);
    L[26] = __pool__COPY(__tmp__140);
    Index __tmp__141 = __pool__XOR(L[8], L[10]);
    __pool__RELEASE(L[27]);
    L[27] = __pool__COPY(__tmp__141);
    Index __tmp__142 = __pool__XOR(L[11], L[14]);
    __pool__RELEASE(L[28]);
    L[28] = __pool__COPY(__tmp__142);
    Index __tmp__143 = __pool__XOR(L[11], L[17]);
    __pool__RELEASE(L[29]);
    L[29] = __pool__COPY(__tmp__143);
    
    Index __tmp__144 = __pool__XOR(L[6], L[24]);
    __pool__RELEASE(src[0]);
    src[0] =  __pool__COPY(__tmp__144);
    
    Index __tmp__145 = __pool__XOR(L[16], L[26]);
    __pool__RELEASE(src[1]);
    src[1] = __pool__COPY(__tmp__145);
    Index __tmp__146 = __pool__XOR(L[19], L[28]);
    __pool__RELEASE(src[2]);
    src[2] = __pool__COPY(__tmp__146);
    Index __tmp__147 = __pool__XOR(L[6], L[21]);
    __pool__RELEASE(src[3]);
    src[3] = __pool__COPY(__tmp__147);
    
    Index __tmp__148 = __pool__XOR(L[20], L[22]);
    __pool__RELEASE(src[4]);
    src[4] = __pool__COPY(__tmp__148);
    Index __tmp__149 = __pool__XOR(L[25], L[29]);
    __pool__RELEASE(src[5]);
    src[5] = __pool__COPY(__tmp__149);
    Index __tmp__150 = __pool__XOR(L[13], L[27]);
    __pool__RELEASE(src[6]);
    src[6] = __pool__COPY(__tmp__150);
    Index __tmp__151 = __pool__XOR(L[6], L[23]);
    __pool__RELEASE(src[7]);
    src[7] = __pool__COPY(__tmp__151);
    
    __pool__RELEASEArray(T, 27);
    __pool__RELEASEArray(M, 63);
    __pool__RELEASEArray(L, 30);
    __pool__RELEASE(__tmp__4);
    __pool__RELEASE(__tmp__5);
    __pool__RELEASE(__tmp__6);
    __pool__RELEASE(__tmp__7);
    __pool__RELEASE(__tmp__8);
    __pool__RELEASE(__tmp__9);
    __pool__RELEASE(__tmp__10);
    __pool__RELEASE(__tmp__11);
    __pool__RELEASE(__tmp__12);
    __pool__RELEASE(__tmp__13);
    __pool__RELEASE(__tmp__14);
    __pool__RELEASE(__tmp__15);
    __pool__RELEASE(__tmp__16);
    __pool__RELEASE(__tmp__17);
    __pool__RELEASE(__tmp__18);
    __pool__RELEASE(__tmp__19);
    __pool__RELEASE(__tmp__20);
    __pool__RELEASE(__tmp__21);
    __pool__RELEASE(__tmp__22);
    __pool__RELEASE(__tmp__23);
    __pool__RELEASE(__tmp__24);
    __pool__RELEASE(__tmp__25);
    __pool__RELEASE(__tmp__26);
    __pool__RELEASE(__tmp__27);
    __pool__RELEASE(__tmp__28);
    __pool__RELEASE(__tmp__29);
    __pool__RELEASE(__tmp__30);
    __pool__RELEASE(__tmp__31);
    __pool__RELEASE(__tmp__32);
    __pool__RELEASE(__tmp__33);
    __pool__RELEASE(__tmp__34);
    __pool__RELEASE(__tmp__35);
    __pool__RELEASE(__tmp__36);
    __pool__RELEASE(__tmp__37);
    __pool__RELEASE(__tmp__38);
    __pool__RELEASE(__tmp__39);
    __pool__RELEASE(__tmp__60);
    __pool__RELEASE(__tmp__61);
    __pool__RELEASE(__tmp__62);
    __pool__RELEASE(__tmp__63);
    __pool__RELEASE(__tmp__64);
    __pool__RELEASE(__tmp__65);
    __pool__RELEASE(__tmp__66);
    __pool__RELEASE(__tmp__67);
    __pool__RELEASE(__tmp__68);
    __pool__RELEASE(__tmp__69);
    __pool__RELEASE(__tmp__70);
    __pool__RELEASE(__tmp__71);
    __pool__RELEASE(__tmp__72);
    __pool__RELEASE(__tmp__73);
    __pool__RELEASE(__tmp__74);
    __pool__RELEASE(__tmp__75);
    __pool__RELEASE(__tmp__76);
    __pool__RELEASE(__tmp__77);
    __pool__RELEASE(__tmp__78);
    __pool__RELEASE(__tmp__79);
    __pool__RELEASE(__tmp__80);
    __pool__RELEASE(__tmp__81);
    __pool__RELEASE(__tmp__82);
    __pool__RELEASE(__tmp__83);
    __pool__RELEASE(__tmp__84);
    __pool__RELEASE(__tmp__85);
    __pool__RELEASE(__tmp__86);
    __pool__RELEASE(__tmp__87);
    __pool__RELEASE(__tmp__88);
    __pool__RELEASE(__tmp__89);
    __pool__RELEASE(__tmp__90);
    __pool__RELEASE(__tmp__91);
    __pool__RELEASE(__tmp__92);
    __pool__RELEASE(__tmp__93);
    __pool__RELEASE(__tmp__94);
    __pool__RELEASE(__tmp__95);
    __pool__RELEASE(__tmp__96);
    __pool__RELEASE(__tmp__97);
    __pool__RELEASE(__tmp__98);
    __pool__RELEASE(__tmp__99);
    __pool__RELEASE(__tmp__100);
    __pool__RELEASE(__tmp__101);
    __pool__RELEASE(__tmp__102);
    __pool__RELEASE(__tmp__103);
    __pool__RELEASE(__tmp__104);
    __pool__RELEASE(__tmp__105);
    __pool__RELEASE(__tmp__106);
    __pool__RELEASE(__tmp__107);
    __pool__RELEASE(__tmp__108);
    __pool__RELEASE(__tmp__109);
    __pool__RELEASE(__tmp__110);
    __pool__RELEASE(__tmp__111);
    __pool__RELEASE(__tmp__112);
    __pool__RELEASE(__tmp__113);
    __pool__RELEASE(__tmp__114);
    __pool__RELEASE(__tmp__115);
    __pool__RELEASE(__tmp__116);
    __pool__RELEASE(__tmp__117);
    __pool__RELEASE(__tmp__118);
    __pool__RELEASE(__tmp__119);
    __pool__RELEASE(__tmp__120);
    __pool__RELEASE(__tmp__121);
    __pool__RELEASE(__tmp__122);
    __pool__RELEASE(__tmp__123);
    __pool__RELEASE(__tmp__124);
    __pool__RELEASE(__tmp__125);
    __pool__RELEASE(__tmp__126);
    __pool__RELEASE(__tmp__127);
    __pool__RELEASE(__tmp__128);
    __pool__RELEASE(__tmp__129);
    __pool__RELEASE(__tmp__130);
    __pool__RELEASE(__tmp__131);
    __pool__RELEASE(__tmp__132);
    __pool__RELEASE(__tmp__133);
    __pool__RELEASE(__tmp__134);
    __pool__RELEASE(__tmp__135);
    __pool__RELEASE(__tmp__136);
    __pool__RELEASE(__tmp__137);
    __pool__RELEASE(__tmp__138);
    __pool__RELEASE(__tmp__139);
    __pool__RELEASE(__tmp__140);
    __pool__RELEASE(__tmp__141);
    __pool__RELEASE(__tmp__142);
    __pool__RELEASE(__tmp__143);
    
    __pool__RELEASE(__tmp__144);
    __pool__RELEASE(__tmp__145);
    __pool__RELEASE(__tmp__146);
    __pool__RELEASE(__tmp__147);
    __pool__RELEASE(__tmp__148);
    __pool__RELEASE(__tmp__149);
    __pool__RELEASE(__tmp__150);
    __pool__RELEASE(__tmp__151);
}

void ShiftRows(Index src[])
{
    Index dst[128];
    __pool__NewArray(dst,128);
    int i;
    int j;
    int k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 8; k++)
            {
                __pool__RELEASE(dst[((i * 32) + (j * 8)) + k]);
                dst[((i * 32) + (j * 8)) + k] = __pool__COPY(src[((i * 32) + (((j + i) % 4) * 8)) + k]);
            }
            
        }
        
    }
    
    for (int i = 0; i < 128; i++)
    {
        __pool__RELEASE(src[i]);
        src[i] = __pool__COPY(dst[i]);
    }
    
    __pool__RELEASEArray(dst, 128);
}

void MixColumn(Index src[])
{
    Index dst[128];
    __pool__NewArray(dst,128);
    int c;
    int i;
    int j;
    Index a02s[32];
    __pool__NewArray(a02s,32);
    for (c = 0; c < 4; c++)
    {
        
        for (i = 0; i < 4; i++)
        {
            Index __tmp__168 = __pool__XOR(src[((c * 8) + (i * 32)) + 7], src[((c * 8) + (i * 32)) + 3]);
            __pool__RELEASE(a02s[(i * 8) + 4]);
            a02s[(i * 8) + 4] = __pool__COPY(__tmp__168);
            Index __tmp__169 = __pool__XOR(src[((c * 8) + (i * 32)) + 7], src[((c * 8) + (i * 32)) + 2]);
            __pool__RELEASE(a02s[(i * 8) + 3]);
            a02s[(i * 8) + 3] = __pool__COPY(__tmp__169);
            Index __tmp__170 = __pool__XOR(src[((c * 8) + (i * 32)) + 7], src[((c * 8) + (i * 32)) + 0]);
            __pool__RELEASE(a02s[(i * 8) + 1]);
            a02s[(i * 8) + 1] = __pool__COPY(__tmp__170);
            __pool__RELEASE(__tmp__168);
            __pool__RELEASE(__tmp__169);
            __pool__RELEASE(__tmp__170);
        }
        
        i = 0;
        {
            Index tmp;
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(src[(c * 8) + 7], src[((c * 8) + 7) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(src[((c * 8) + 7) + 64], src[((c * 8) + 7) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(src[((c * 8) + 7) + 64], src[((c * 8) + 7) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(src[((c * 8) + 7) + 96], src[(c * 8) + 7]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
            __pool__RELEASE(tmp);
        }
        
        i = 2;
        {
            Index tmp;
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(src[(c * 8) + 1], src[((c * 8) + 1) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(src[((c * 8) + 1) + 64], src[((c * 8) + 1) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(src[((c * 8) + 1) + 64], src[((c * 8) + 1) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(src[((c * 8) + 1) + 96], src[(c * 8) + 1]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
            __pool__RELEASE(tmp);
        }
        for (i = 5; i < 8; i++)
        {
            Index __tmp__176 = __pool__XOR(src[((c * 8) - 1) + i], src[(((c * 8) - 1) + 32) + i]);
            __pool__RELEASE(dst[(c * 8) + i]);
            dst[(c * 8) + i] = __pool__COPY(__tmp__176);
            Index __tmp__177 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
            __pool__RELEASE(dst[(c * 8) + i]);
            dst[(c * 8) + i] = __pool__COPY(__tmp__177);
            Index __tmp__178 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
            __pool__RELEASE(dst[(c * 8) + i]);
            dst[(c * 8) + i] = __pool__COPY(__tmp__178);
            Index __tmp__179 = __pool__XOR(src[(((c * 8) - 1) + i) + 64], src[(((c * 8) - 1) + 32) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 32]);
            dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__179);
            Index __tmp__180 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 32]);
            dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__180);
            Index __tmp__181 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
            __pool__RELEASE(dst[((c * 8) + i) + 32]);
            dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__181);
            Index __tmp__182 = __pool__XOR(src[(((c * 8) - 1) + i) + 64], src[(((c * 8) - 1) + 96) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 64]);
            dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__182);
            Index __tmp__183 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 64]);
            dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__183);
            Index __tmp__184 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
            __pool__RELEASE(dst[((c * 8) + i) + 64]);
            dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__184);
            Index __tmp__185 = __pool__XOR(src[(((c * 8) - 1) + i) + 96], src[((c * 8) - 1) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 96]);
            dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__185);
            Index __tmp__186 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
            __pool__RELEASE(dst[((c * 8) + i) + 96]);
            dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__186);
            Index __tmp__187 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
            __pool__RELEASE(dst[((c * 8) + i) + 96]);
            dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__187);
            __pool__RELEASE(__tmp__176);
            __pool__RELEASE(__tmp__177);
            __pool__RELEASE(__tmp__178);
            __pool__RELEASE(__tmp__179);
            __pool__RELEASE(__tmp__180);
            __pool__RELEASE(__tmp__181);
            __pool__RELEASE(__tmp__182);
            __pool__RELEASE(__tmp__183);
            __pool__RELEASE(__tmp__184);
            __pool__RELEASE(__tmp__185);
            __pool__RELEASE(__tmp__186);
            __pool__RELEASE(__tmp__187);
        }

        i = 1;
        {
            Index tmp;
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(a02s[i], a02s[(1 * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i];
            dst[(c * 8) + i] = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(a02s[(2 * 8) + i], a02s[(1 * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+32];
            dst[((c * 8) + i) + 32] = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(a02s[(2 * 8) + i], a02s[(3 * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+64];
            dst[((c * 8) + i) + 64] = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(a02s[(3 * 8) + i], a02s[(0 * 8) + i]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
            __pool__RELEASE(tmp);
            
            tmp=dst[(c * 8) + i+96];
            dst[((c * 8) + i) + 96] = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
            __pool__RELEASE(tmp);
        }
        for (i = 3; i <= 4; i++)
        {
            Index __tmp__191 = __pool__XOR(a02s[(0 * 8) + i], a02s[(1 * 8) + i]);
            __pool__RELEASE(dst[(c * 8) + i]);
            dst[(c * 8) + i] = __pool__COPY(__tmp__191);
            Index __tmp__192 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
            __pool__RELEASE(dst[(c * 8) + i]);
            dst[(c * 8) + i] = __pool__COPY(__tmp__192);
            Index __tmp__193 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
            __pool__RELEASE(dst[(c * 8) + i]);
            dst[(c * 8) + i] = __pool__COPY(__tmp__193);
            Index __tmp__194 = __pool__XOR(a02s[(2 * 8) + i], a02s[(1 * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 32]);
            dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__194);
            Index __tmp__195 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 32]);
            dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__195);
            Index __tmp__196 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
            __pool__RELEASE(dst[((c * 8) + i) + 32]);
            dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__196);
            Index __tmp__197 = __pool__XOR(a02s[(2 * 8) + i], a02s[(3 * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 64]);
            dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__197);
            Index __tmp__198 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 64]);
            dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__198);
            Index __tmp__199 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
            __pool__RELEASE(dst[((c * 8) + i) + 64]);
            dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__199);
            Index __tmp__200 = __pool__XOR(a02s[(3 * 8) + i], a02s[(0 * 8) + i]);
            __pool__RELEASE(dst[((c * 8) + i) + 96]);
            dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__200);
            Index __tmp__201 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
            __pool__RELEASE(dst[((c * 8) + i) + 96]);
            dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__201);
            Index __tmp__202 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
            __pool__RELEASE(dst[((c * 8) + i) + 96]);
            dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__202);
            __pool__RELEASE(__tmp__191);
            __pool__RELEASE(__tmp__192);
            __pool__RELEASE(__tmp__193);
            __pool__RELEASE(__tmp__194);
            __pool__RELEASE(__tmp__195);
            __pool__RELEASE(__tmp__196);
            __pool__RELEASE(__tmp__197);
            __pool__RELEASE(__tmp__198);
            __pool__RELEASE(__tmp__199);
            __pool__RELEASE(__tmp__200);
            __pool__RELEASE(__tmp__201);
            __pool__RELEASE(__tmp__202);
        }
        
    }
    /*
     for (int i = 0; i < 128; i++)
     {
     __pool__RELEASE(src[i]);
     src[i] = __pool__COPY(dst[i]);
     }
     */
    __pool__RELEASEArray(dst, 128);
    __pool__RELEASEArray(a02s, 32);
}

void RotWord(Index a[])
{
    Index tmp = __pool__NewVar();
    int i;
    int j;
    
    for (i = 0; i < 8; i++)
    {
        __pool__RELEASE(tmp);
        tmp = __pool__COPY(a[i]);
        
        for (j = 0; j < 3; j++)
        {
            __pool__RELEASE(a[(j * 8) + i] );
            a[(j * 8) + i] = __pool__COPY(a[((j * 8) + i) + 8]);
        }
        __pool__RELEASE(a[24+i]);
        a[24 + i] = __pool__COPY(tmp);
        
    }
    
    
    __pool__RELEASE(tmp);
}

void Mul2(Index b[])
{
    
    Index tmp = __pool__NewVar();
    __pool__RELEASE(tmp);
    tmp = __pool__COPY(b[7]);
    __pool__RELEASE(b[7]);
    b[7] = __pool__COPY(b[6]);
    __pool__RELEASE(b[6]);
    b[6] = __pool__COPY(b[5]);
    __pool__RELEASE(b[5]);
    b[5] = __pool__COPY(b[4]);
    Index __tmp__216 = __pool__XOR(b[3], tmp);
    __pool__RELEASE(b[4]);
    b[4] = __pool__COPY(__tmp__216);
    Index __tmp__217 = __pool__XOR(b[2], tmp);
    __pool__RELEASE(b[3]);
    b[3] = __pool__COPY(__tmp__217);
    __pool__RELEASE(b[2]);
    b[2] = __pool__COPY(b[1]);
    Index __tmp__219 = __pool__XOR(b[0], tmp);
    __pool__RELEASE(b[1]);
    b[1] = __pool__COPY(__tmp__219);
    __pool__RELEASE(b[0]);
    b[0] = __pool__COPY(tmp);
    __pool__RELEASE(tmp);
    __pool__RELEASE(__tmp__216);
    __pool__RELEASE(__tmp__217);
    __pool__RELEASE(__tmp__219);
}

void KEYEXPENSION(Index AESROUNDKEY[], Index AESKEY[])
{
    Index Rcon[8];
    __pool__NewArray(Rcon,8);
    Index tmp[32];
    __pool__NewArray(tmp,32);
    Index tmps[8];
    __pool__NewArray(tmps,8);
    int i;
    int j;
    for (i = 0; i < 8; i++)
    {
        __pool__RELEASE(Rcon[i]);
        Rcon[i] = __pool__COPY(Zero);
    }
    
    __pool__RELEASE(Rcon[1]);
    Rcon[1] = __pool__COPY(One);
    for (i = 0; i < 128; i++)
    {
        AESROUNDKEY[i] = __pool__COPY(AESKEY[i]);
    }
    
    for (i = 4; i < 44; i++)
    {
        
        for (j = 0; j < 32; j++)
        {
            __pool__RELEASE(tmp[j]);
            tmp[j] = __pool__COPY(AESROUNDKEY[((i - 1) * 32) + j]);
        }
        
        if ((i % 4) == 0)
        {
            RotWord(tmp);
            
            for (j = 0; j < 4; j++)
            {
                GFINV(&tmp[8 * j]);
            }
            
             for (j = 0; j < 8; j++)
             {
             __pool__RELEASE(tmp[j]);
             tmp[j] = __pool__XOR(tmp[j], Rcon[j]);
             }
             Mul2(Rcon);
            
        }
        
        for (j = 0; j < 32; j++)
        {
            AESROUNDKEY[(i * 32) + j] = __pool__XOR(AESROUNDKEY[((i * 32) + j) - 128], tmp[j]);
        }
    }
    
    __pool__RELEASEArray(Rcon, 8);
    __pool__RELEASEArray(tmp, 32);
    __pool__RELEASEArray(tmps, 8);
}
void AddRoundKey(Index ROUNDKEY[],Index MSG[],int round)
{
    int i;
    for(i=0;i<128;i++)
    {
        __pool__RELEASE(MSG[i]);
        MSG[i]=__pool__XOR(MSG[i],ROUNDKEY[128*round+i]);
    }
}
void SubBytes(Index MSG[])
{
    int i=0;
    for(i=0;i<16;i++)
        GFINV(&(MSG[i*8]));
}
void AES(Index *input)
{
    int i;
    Index AESROUNDKEY[1408];
    __pool__NewArray(AESROUNDKEY,1408);
    KEYEXPENSION(AESROUNDKEY, &input[128]);
    for (i = 1; i < 10; i++)
    {
        SubBytes(input);
        ShiftRows(input);
        MixColumn(input);
        AddRoundKey(AESROUNDKEY, input, i);
    }
    SubBytes(input);
    ShiftRows(input);
    AddRoundKey(AESROUNDKEY, input, i);
    __pool__RELEASEArray(AESROUNDKEY, 1408);
}
void MAES(int n)
{
    Index array[256];
    for(int i=0;i<256;i++)
        array[i]=__pool__COPY(One);
    auto t0=clock_start();
    for(int i=0;i<n;i++)
    {
        AES(array);
    }
    __pool__RELEASEArray(array,256);
    S.Close();
    double t1=time_from(t0);
    printf("Time=%lf\n",t1/1000000);
    S.PrintCount();
    
}
int main(int argc,char ** argv)
{
    auto t=clock_start();
    printf("Party Num=%d\n",PartyNumber);
    if(argc<=3) return 0;
    int port;
    int MyID;
    MyID=atoi(argv[1]);
    port=atoi(argv[2]);
    block D=_mm_set_epi32(0x0,1<<MyID,0xffffffff,0xffffffff);
    //block D=_mm_set_epi32(0,MyID,0,1);
    block seed=_mm_set_epi32(0,0,0,MyID+100);
    Map.Setup(MainWireArraySize);
    IO.Setup(MyID,PartyNumber,port);
    MOT.Setup(MyID,D,MainBuffer,seed,&IO);
    MP.Setup(MyID,MainPoolSize,MainBucketSize,MainBuffer,&MOT);
    S.Setup(MyID,MainStageSize,&MP,&Map);
    Zero=Map.Zero;
    One=Map.One;
    printf("Setup cost: %lfs\n",time_from(t)/1000000);
    IO.PrintCount();
    int n;
    n=atoi(argv[3]);
    MAES(n);
}
