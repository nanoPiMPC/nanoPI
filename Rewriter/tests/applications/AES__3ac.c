typedef int Index;
typedef int bit;
extern Index Zero;
extern Index One;
void GFINV(bit src[])
{
  bit T[27]; __pool__NewArray(T, 27);
  bit M[63]; __pool__NewArray(M, 63);
  bit L[30]; __pool__NewArray(L, 30);
  bit __tmp__4 = __pool__XOR(src[0], src[3]);
  __pool__RELEASE(T[0]);
  T[0] = __pool__COPY(__tmp__4);
  bit __tmp__5 = __pool__XOR(src[0], src[5]);
  __pool__RELEASE(T[1]);
  T[1] = __pool__COPY(__tmp__5);
  bit __tmp__6 = __pool__XOR(src[0], src[6]);
  __pool__RELEASE(T[2]);
  T[2] = __pool__COPY(__tmp__6);
  bit __tmp__7 = __pool__XOR(src[3], src[5]);
  __pool__RELEASE(T[3]);
  T[3] = __pool__COPY(__tmp__7);
  bit __tmp__8 = __pool__XOR(src[4], src[6]);
  __pool__RELEASE(T[4]);
  T[4] = __pool__COPY(__tmp__8);
  bit __tmp__9 = __pool__XOR(T[0], T[4]);
  __pool__RELEASE(T[5]);
  T[5] = __pool__COPY(__tmp__9);
  bit __tmp__10 = __pool__XOR(src[1], src[2]);
  __pool__RELEASE(T[6]);
  T[6] = __pool__COPY(__tmp__10);
  bit __tmp__11 = __pool__XOR(src[7], T[5]);
  __pool__RELEASE(T[7]);
  T[7] = __pool__COPY(__tmp__11);
  bit __tmp__12 = __pool__XOR(src[7], T[6]);
  __pool__RELEASE(T[8]);
  T[8] = __pool__COPY(__tmp__12);
  bit __tmp__13 = __pool__XOR(T[5], T[6]);
  __pool__RELEASE(T[9]);
  T[9] = __pool__COPY(__tmp__13);
  bit __tmp__14 = __pool__XOR(src[1], src[5]);
  __pool__RELEASE(T[10]);
  T[10] = __pool__COPY(__tmp__14);
  bit __tmp__15 = __pool__XOR(src[2], src[5]);
  __pool__RELEASE(T[11]);
  T[11] = __pool__COPY(__tmp__15);
  bit __tmp__16 = __pool__XOR(T[2], T[3]);
  __pool__RELEASE(T[12]);
  T[12] = __pool__COPY(__tmp__16);
  bit __tmp__17 = __pool__XOR(T[5], T[10]);
  __pool__RELEASE(T[13]);
  T[13] = __pool__COPY(__tmp__17);
  bit __tmp__18 = __pool__XOR(T[4], T[10]);
  __pool__RELEASE(T[14]);
  T[14] = __pool__COPY(__tmp__18);
  bit __tmp__19 = __pool__XOR(T[4], T[11]);
  __pool__RELEASE(T[15]);
  T[15] = __pool__COPY(__tmp__19);
  bit __tmp__20 = __pool__XOR(T[8], T[15]);
  __pool__RELEASE(T[16]);
  T[16] = __pool__COPY(__tmp__20);
  bit __tmp__21 = __pool__XOR(src[3], src[7]);
  __pool__RELEASE(T[17]);
  T[17] = __pool__COPY(__tmp__21);
  bit __tmp__22 = __pool__XOR(T[6], T[17]);
  __pool__RELEASE(T[18]);
  T[18] = __pool__COPY(__tmp__22);
  bit __tmp__23 = __pool__XOR(T[0], T[18]);
  __pool__RELEASE(T[19]);
  T[19] = __pool__COPY(__tmp__23);
  bit __tmp__24 = __pool__XOR(src[6], src[7]);
  __pool__RELEASE(T[20]);
  T[20] = __pool__COPY(__tmp__24);
  bit __tmp__25 = __pool__XOR(T[6], T[20]);
  __pool__RELEASE(T[21]);
  T[21] = __pool__COPY(__tmp__25);
  bit __tmp__26 = __pool__XOR(T[1], T[21]);
  __pool__RELEASE(T[22]);
  T[22] = __pool__COPY(__tmp__26);
  bit __tmp__27 = __pool__XOR(T[1], T[9]);
  __pool__RELEASE(T[23]);
  T[23] = __pool__COPY(__tmp__27);
  bit __tmp__28 = __pool__XOR(T[19], T[16]);
  __pool__RELEASE(T[24]);
  T[24] = __pool__COPY(__tmp__28);
  bit __tmp__29 = __pool__XOR(T[2], T[15]);
  __pool__RELEASE(T[25]);
  T[25] = __pool__COPY(__tmp__29);
  bit __tmp__30 = __pool__XOR(T[0], T[11]);
  __pool__RELEASE(T[26]);
  T[26] = __pool__COPY(__tmp__30);
  bit __tmp__31 = __pool__AND(T[5], T[12]);
  __pool__RELEASE(M[0]);
  M[0] = __pool__COPY(__tmp__31);
  bit __tmp__32 = __pool__AND(T[7], T[22]);
  __pool__RELEASE(M[1]);
  M[1] = __pool__COPY(__tmp__32);
  bit __tmp__33 = __pool__AND(src[7], T[18]);
  __pool__RELEASE(M[3]);
  M[3] = __pool__COPY(__tmp__33);
  bit __tmp__34 = __pool__AND(T[2], T[15]);
  __pool__RELEASE(M[5]);
  M[5] = __pool__COPY(__tmp__34);
  bit __tmp__35 = __pool__AND(T[8], T[21]);
  __pool__RELEASE(M[6]);
  M[6] = __pool__COPY(__tmp__35);
  bit __tmp__36 = __pool__AND(T[16], T[19]);
  __pool__RELEASE(M[8]);
  M[8] = __pool__COPY(__tmp__36);
  bit __tmp__37 = __pool__AND(T[0], T[14]);
  __pool__RELEASE(M[10]);
  M[10] = __pool__COPY(__tmp__37);
  bit __tmp__38 = __pool__AND(T[3], T[26]);
  __pool__RELEASE(M[11]);
  M[11] = __pool__COPY(__tmp__38);
  bit __tmp__39 = __pool__AND(T[1], T[9]);
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
  bit __tmp__60 = __pool__XOR(M[2], M[0]);
  __pool__RELEASE(M[2]);
  M[2] = __pool__COPY(__tmp__60);
  bit __tmp__61 = __pool__XOR(M[3], M[0]);
  __pool__RELEASE(M[4]);
  M[4] = __pool__COPY(__tmp__61);
  bit __tmp__62 = __pool__XOR(M[7], M[5]);
  __pool__RELEASE(M[7]);
  M[7] = __pool__COPY(__tmp__62);
  bit __tmp__63 = __pool__XOR(M[8], M[5]);
  __pool__RELEASE(M[9]);
  M[9] = __pool__COPY(__tmp__63);
  bit __tmp__64 = __pool__XOR(M[10], M[11]);
  __pool__RELEASE(M[12]);
  M[12] = __pool__COPY(__tmp__64);
  bit __tmp__65 = __pool__XOR(M[10], M[13]);
  __pool__RELEASE(M[14]);
  M[14] = __pool__COPY(__tmp__65);
  bit __tmp__66 = __pool__XOR(M[2], M[1]);
  __pool__RELEASE(M[15]);
  M[15] = __pool__COPY(__tmp__66);
  bit __tmp__67 = __pool__XOR(M[4], M[15]);
  __pool__RELEASE(M[16]);
  M[16] = __pool__COPY(__tmp__67);
  bit __tmp__68 = __pool__XOR(M[6], M[7]);
  __pool__RELEASE(M[17]);
  M[17] = __pool__COPY(__tmp__68);
  bit __tmp__69 = __pool__XOR(M[9], M[14]);
  __pool__RELEASE(M[18]);
  M[18] = __pool__COPY(__tmp__69);
  bit __tmp__70 = __pool__XOR(M[15], M[12]);
  __pool__RELEASE(M[19]);
  M[19] = __pool__COPY(__tmp__70);
  bit __tmp__71 = __pool__XOR(M[16], M[14]);
  __pool__RELEASE(M[20]);
  M[20] = __pool__COPY(__tmp__71);
  bit __tmp__72 = __pool__XOR(M[12], M[17]);
  __pool__RELEASE(M[21]);
  M[21] = __pool__COPY(__tmp__72);
  bit __tmp__73 = __pool__XOR(M[18], M[21]);
  __pool__RELEASE(M[22]);
  M[22] = __pool__COPY(__tmp__73);
  bit __tmp__74 = __pool__XOR(M[21], M[22]);
  __pool__RELEASE(M[23]);
  M[23] = __pool__COPY(__tmp__74);
  bit __tmp__75 = __pool__XOR(M[19], M[20]);
  __pool__RELEASE(M[26]);
  M[26] = __pool__COPY(__tmp__75);
  bit __tmp__76 = __pool__AND(M[19], M[21]);
  __pool__RELEASE(M[24]);
  M[24] = __pool__COPY(__tmp__76);
  bit __tmp__77 = __pool__AND(M[19], M[22]);
  __pool__RELEASE(M[30]);
  M[30] = __pool__COPY(__tmp__77);
  bit __tmp__78 = __pool__AND(M[20], M[21]);
  __pool__RELEASE(M[33]);
  M[33] = __pool__COPY(__tmp__78);
  bit __tmp__79 = __pool__XOR(M[20], M[24]);
  __pool__RELEASE(M[25]);
  M[25] = __pool__COPY(__tmp__79);
  bit __tmp__80 = __pool__XOR(M[22], M[24]);
  __pool__RELEASE(M[27]);
  M[27] = __pool__COPY(__tmp__80);
  bit __tmp__81 = __pool__XOR(M[26], M[24]);
  __pool__RELEASE(M[32]);
  M[32] = __pool__COPY(__tmp__81);
  bit __tmp__82 = __pool__XOR(M[23], M[24]);
  __pool__RELEASE(M[35]);
  M[35] = __pool__COPY(__tmp__82);
  bit __tmp__83 = __pool__AND(M[26], M[27]);
  __pool__RELEASE(M[28]);
  M[28] = __pool__COPY(__tmp__83);
  bit __tmp__84 = __pool__AND(M[23], M[25]);
  __pool__RELEASE(M[29]);
  M[29] = __pool__COPY(__tmp__84);
  bit __tmp__85 = __pool__AND(M[26], M[30]);
  __pool__RELEASE(M[31]);
  M[31] = __pool__COPY(__tmp__85);
  bit __tmp__86 = __pool__AND(M[23], M[33]);
  __pool__RELEASE(M[34]);
  M[34] = __pool__COPY(__tmp__86);
  bit __tmp__87 = __pool__XOR(M[20], M[28]);
  __pool__RELEASE(M[36]);
  M[36] = __pool__COPY(__tmp__87);
  bit __tmp__88 = __pool__XOR(M[31], M[32]);
  __pool__RELEASE(M[37]);
  M[37] = __pool__COPY(__tmp__88);
  bit __tmp__89 = __pool__XOR(M[22], M[29]);
  __pool__RELEASE(M[38]);
  M[38] = __pool__COPY(__tmp__89);
  bit __tmp__90 = __pool__XOR(M[34], M[35]);
  __pool__RELEASE(M[39]);
  M[39] = __pool__COPY(__tmp__90);
  bit __tmp__91 = __pool__XOR(M[37], M[39]);
  __pool__RELEASE(M[40]);
  M[40] = __pool__COPY(__tmp__91);
  bit __tmp__92 = __pool__XOR(M[36], M[38]);
  __pool__RELEASE(M[41]);
  M[41] = __pool__COPY(__tmp__92);
  bit __tmp__93 = __pool__XOR(M[36], M[37]);
  __pool__RELEASE(M[42]);
  M[42] = __pool__COPY(__tmp__93);
  bit __tmp__94 = __pool__XOR(M[38], M[39]);
  __pool__RELEASE(M[43]);
  M[43] = __pool__COPY(__tmp__94);
  bit __tmp__95 = __pool__XOR(M[41], M[30]);
  __pool__RELEASE(M[44]);
  M[44] = __pool__COPY(__tmp__95);
  bit __tmp__96 = __pool__AND(M[45], M[43]);
  __pool__RELEASE(M[45]);
  M[45] = __pool__COPY(__tmp__96);
  bit __tmp__97 = __pool__AND(M[46], M[39]);
  __pool__RELEASE(M[46]);
  M[46] = __pool__COPY(__tmp__97);
  bit __tmp__98 = __pool__AND(M[47], M[38]);
  __pool__RELEASE(M[47]);
  M[47] = __pool__COPY(__tmp__98);
  bit __tmp__99 = __pool__AND(M[48], M[42]);
  __pool__RELEASE(M[48]);
  M[48] = __pool__COPY(__tmp__99);
  bit __tmp__100 = __pool__AND(M[49], M[37]);
  __pool__RELEASE(M[49]);
  M[49] = __pool__COPY(__tmp__100);
  bit __tmp__101 = __pool__AND(M[50], M[36]);
  __pool__RELEASE(M[50]);
  M[50] = __pool__COPY(__tmp__101);
  bit __tmp__102 = __pool__AND(M[51], M[41]);
  __pool__RELEASE(M[51]);
  M[51] = __pool__COPY(__tmp__102);
  bit __tmp__103 = __pool__AND(M[52], M[44]);
  __pool__RELEASE(M[52]);
  M[52] = __pool__COPY(__tmp__103);
  bit __tmp__104 = __pool__AND(M[53], M[40]);
  __pool__RELEASE(M[53]);
  M[53] = __pool__COPY(__tmp__104);
  bit __tmp__105 = __pool__AND(M[54], M[43]);
  __pool__RELEASE(M[54]);
  M[54] = __pool__COPY(__tmp__105);
  bit __tmp__106 = __pool__AND(M[55], M[39]);
  __pool__RELEASE(M[55]);
  M[55] = __pool__COPY(__tmp__106);
  bit __tmp__107 = __pool__AND(M[56], M[38]);
  __pool__RELEASE(M[56]);
  M[56] = __pool__COPY(__tmp__107);
  bit __tmp__108 = __pool__AND(M[57], M[42]);
  __pool__RELEASE(M[57]);
  M[57] = __pool__COPY(__tmp__108);
  bit __tmp__109 = __pool__AND(M[58], M[37]);
  __pool__RELEASE(M[58]);
  M[58] = __pool__COPY(__tmp__109);
  bit __tmp__110 = __pool__AND(M[59], M[36]);
  __pool__RELEASE(M[59]);
  M[59] = __pool__COPY(__tmp__110);
  bit __tmp__111 = __pool__AND(M[60], M[41]);
  __pool__RELEASE(M[60]);
  M[60] = __pool__COPY(__tmp__111);
  bit __tmp__112 = __pool__AND(M[61], M[44]);
  __pool__RELEASE(M[61]);
  M[61] = __pool__COPY(__tmp__112);
  bit __tmp__113 = __pool__AND(M[62], M[40]);
  __pool__RELEASE(M[62]);
  M[62] = __pool__COPY(__tmp__113);
  bit __tmp__114 = __pool__XOR(M[60], M[61]);
  __pool__RELEASE(L[0]);
  L[0] = __pool__COPY(__tmp__114);
  bit __tmp__115 = __pool__XOR(M[49], M[55]);
  __pool__RELEASE(L[1]);
  L[1] = __pool__COPY(__tmp__115);
  bit __tmp__116 = __pool__XOR(M[45], M[47]);
  __pool__RELEASE(L[2]);
  L[2] = __pool__COPY(__tmp__116);
  bit __tmp__117 = __pool__XOR(M[46], M[54]);
  __pool__RELEASE(L[3]);
  L[3] = __pool__COPY(__tmp__117);
  bit __tmp__118 = __pool__XOR(M[53], M[57]);
  __pool__RELEASE(L[4]);
  L[4] = __pool__COPY(__tmp__118);
  bit __tmp__119 = __pool__XOR(M[48], M[60]);
  __pool__RELEASE(L[5]);
  L[5] = __pool__COPY(__tmp__119);
  bit __tmp__120 = __pool__XOR(M[61], L[5]);
  __pool__RELEASE(L[6]);
  L[6] = __pool__COPY(__tmp__120);
  bit __tmp__121 = __pool__XOR(M[45], L[3]);
  __pool__RELEASE(L[7]);
  L[7] = __pool__COPY(__tmp__121);
  bit __tmp__122 = __pool__XOR(M[50], M[58]);
  __pool__RELEASE(L[8]);
  L[8] = __pool__COPY(__tmp__122);
  bit __tmp__123 = __pool__XOR(M[51], M[52]);
  __pool__RELEASE(L[9]);
  L[9] = __pool__COPY(__tmp__123);
  bit __tmp__124 = __pool__XOR(M[52], L[4]);
  __pool__RELEASE(L[10]);
  L[10] = __pool__COPY(__tmp__124);
  bit __tmp__125 = __pool__XOR(M[59], L[2]);
  __pool__RELEASE(L[11]);
  L[11] = __pool__COPY(__tmp__125);
  bit __tmp__126 = __pool__XOR(M[47], M[50]);
  __pool__RELEASE(L[12]);
  L[12] = __pool__COPY(__tmp__126);
  bit __tmp__127 = __pool__XOR(M[49], L[0]);
  __pool__RELEASE(L[13]);
  L[13] = __pool__COPY(__tmp__127);
  bit __tmp__128 = __pool__XOR(M[51], M[60]);
  __pool__RELEASE(L[14]);
  L[14] = __pool__COPY(__tmp__128);
  bit __tmp__129 = __pool__XOR(M[54], L[1]);
  __pool__RELEASE(L[15]);
  L[15] = __pool__COPY(__tmp__129);
  bit __tmp__130 = __pool__XOR(M[55], L[0]);
  __pool__RELEASE(L[16]);
  L[16] = __pool__COPY(__tmp__130);
  bit __tmp__131 = __pool__XOR(M[56], L[1]);
  __pool__RELEASE(L[17]);
  L[17] = __pool__COPY(__tmp__131);
  bit __tmp__132 = __pool__XOR(M[57], L[8]);
  __pool__RELEASE(L[18]);
  L[18] = __pool__COPY(__tmp__132);
  bit __tmp__133 = __pool__XOR(M[62], L[4]);
  __pool__RELEASE(L[19]);
  L[19] = __pool__COPY(__tmp__133);
  bit __tmp__134 = __pool__XOR(L[0], L[1]);
  __pool__RELEASE(L[20]);
  L[20] = __pool__COPY(__tmp__134);
  bit __tmp__135 = __pool__XOR(L[1], L[7]);
  __pool__RELEASE(L[21]);
  L[21] = __pool__COPY(__tmp__135);
  bit __tmp__136 = __pool__XOR(L[3], L[12]);
  __pool__RELEASE(L[22]);
  L[22] = __pool__COPY(__tmp__136);
  bit __tmp__137 = __pool__XOR(L[18], L[2]);
  __pool__RELEASE(L[23]);
  L[23] = __pool__COPY(__tmp__137);
  bit __tmp__138 = __pool__XOR(L[15], L[9]);
  __pool__RELEASE(L[24]);
  L[24] = __pool__COPY(__tmp__138);
  bit __tmp__139 = __pool__XOR(L[6], L[10]);
  __pool__RELEASE(L[25]);
  L[25] = __pool__COPY(__tmp__139);
  bit __tmp__140 = __pool__XOR(L[7], L[9]);
  __pool__RELEASE(L[26]);
  L[26] = __pool__COPY(__tmp__140);
  bit __tmp__141 = __pool__XOR(L[8], L[10]);
  __pool__RELEASE(L[27]);
  L[27] = __pool__COPY(__tmp__141);
  bit __tmp__142 = __pool__XOR(L[11], L[14]);
  __pool__RELEASE(L[28]);
  L[28] = __pool__COPY(__tmp__142);
  bit __tmp__143 = __pool__XOR(L[11], L[17]);
  __pool__RELEASE(L[29]);
  L[29] = __pool__COPY(__tmp__143);
  bit __tmp__144 = __pool__XOR(L[6], L[24]);
  __pool__RELEASE(src[0]);
  src[0] = __pool__COPY(__tmp__144);
  bit __tmp__145 = __pool__XOR(L[16], L[26]);
  __pool__RELEASE(src[1]);
  src[1] = __pool__COPY(__tmp__145);
  bit __tmp__146 = __pool__XOR(L[19], L[28]);
  __pool__RELEASE(src[2]);
  src[2] = __pool__COPY(__tmp__146);
  bit __tmp__147 = __pool__XOR(L[6], L[21]);
  __pool__RELEASE(src[3]);
  src[3] = __pool__COPY(__tmp__147);
  bit __tmp__148 = __pool__XOR(L[20], L[22]);
  __pool__RELEASE(src[4]);
  src[4] = __pool__COPY(__tmp__148);
  bit __tmp__149 = __pool__XOR(L[25], L[29]);
  __pool__RELEASE(src[5]);
  src[5] = __pool__COPY(__tmp__149);
  bit __tmp__150 = __pool__XOR(L[13], L[27]);
  __pool__RELEASE(src[6]);
  src[6] = __pool__COPY(__tmp__150);
  bit __tmp__151 = __pool__XOR(L[6], L[23]);
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

void ShiftRows(bit src[])
{
  bit dst[128]; __pool__NewArray(dst, 128);
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

void MixColumn(bit src[])
{
  bit dst[128]; __pool__NewArray(dst, 128);
  int c;
  int i;
  int j;
  bit a02s[32]; __pool__NewArray(a02s, 32);
  for (c = 0; c < 4; c++)
  {
    for (i = 0; i < 4; i++)
    {
      bit __tmp__168 = __pool__XOR(src[((c * 8) + (i * 32)) + 7], src[((c * 8) + (i * 32)) + 3]);
      __pool__RELEASE(a02s[(i * 8) + 4]);
      a02s[(i * 8) + 4] = __pool__COPY(__tmp__168);
      bit __tmp__169 = __pool__XOR(src[((c * 8) + (i * 32)) + 7], src[((c * 8) + (i * 32)) + 2]);
      __pool__RELEASE(a02s[(i * 8) + 3]);
      a02s[(i * 8) + 3] = __pool__COPY(__tmp__169);
      bit __tmp__170 = __pool__XOR(src[((c * 8) + (i * 32)) + 7], src[((c * 8) + (i * 32)) + 0]);
      __pool__RELEASE(a02s[(i * 8) + 1]);
      a02s[(i * 8) + 1] = __pool__COPY(__tmp__170);
      __pool__RELEASE(__tmp__168);
      __pool__RELEASE(__tmp__169);
      __pool__RELEASE(__tmp__170);
    }

    i = 0;
    bit __tmp__172 = __pool__XOR(src[(c * 8) + 7], src[((c * 8) + 7) + 32]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__172);
    bit __tmp__173 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__173);
    bit __tmp__174 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__174);
    bit __tmp__175 = __pool__XOR(src[((c * 8) + 7) + 64], src[((c * 8) + 7) + 32]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__175);
    bit __tmp__176 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__176);
    bit __tmp__177 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__177);
    bit __tmp__178 = __pool__XOR(src[((c * 8) + 7) + 64], src[((c * 8) + 7) + 96]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__178);
    bit __tmp__179 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__179);
    bit __tmp__180 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__180);
    bit __tmp__181 = __pool__XOR(src[((c * 8) + 7) + 96], src[(c * 8) + 7]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__181);
    bit __tmp__182 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__182);
    bit __tmp__183 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__183);
    i = 2;
    bit __tmp__185 = __pool__XOR(src[(c * 8) + 1], src[((c * 8) + 1) + 32]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__185);
    bit __tmp__186 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__186);
    bit __tmp__187 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__187);
    bit __tmp__188 = __pool__XOR(src[((c * 8) + 1) + 64], src[((c * 8) + 1) + 32]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__188);
    bit __tmp__189 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__189);
    bit __tmp__190 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__190);
    bit __tmp__191 = __pool__XOR(src[((c * 8) + 1) + 64], src[((c * 8) + 1) + 96]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__191);
    bit __tmp__192 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__192);
    bit __tmp__193 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__193);
    bit __tmp__194 = __pool__XOR(src[((c * 8) + 1) + 96], src[(c * 8) + 1]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__194);
    bit __tmp__195 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__195);
    bit __tmp__196 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__196);
    for (i = 5; i < 8; i++)
    {
      bit __tmp__198 = __pool__XOR(src[((c * 8) - 1) + i], src[(((c * 8) - 1) + 32) + i]);
      __pool__RELEASE(dst[(c * 8) + i]);
      dst[(c * 8) + i] = __pool__COPY(__tmp__198);
      bit __tmp__199 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
      __pool__RELEASE(dst[(c * 8) + i]);
      dst[(c * 8) + i] = __pool__COPY(__tmp__199);
      bit __tmp__200 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
      __pool__RELEASE(dst[(c * 8) + i]);
      dst[(c * 8) + i] = __pool__COPY(__tmp__200);
      bit __tmp__201 = __pool__XOR(src[(((c * 8) - 1) + i) + 64], src[(((c * 8) - 1) + 32) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 32]);
      dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__201);
      bit __tmp__202 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 32]);
      dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__202);
      bit __tmp__203 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
      __pool__RELEASE(dst[((c * 8) + i) + 32]);
      dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__203);
      bit __tmp__204 = __pool__XOR(src[(((c * 8) - 1) + i) + 64], src[(((c * 8) - 1) + 96) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 64]);
      dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__204);
      bit __tmp__205 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 64]);
      dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__205);
      bit __tmp__206 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
      __pool__RELEASE(dst[((c * 8) + i) + 64]);
      dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__206);
      bit __tmp__207 = __pool__XOR(src[(((c * 8) - 1) + i) + 96], src[((c * 8) - 1) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 96]);
      dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__207);
      bit __tmp__208 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
      __pool__RELEASE(dst[((c * 8) + i) + 96]);
      dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__208);
      bit __tmp__209 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
      __pool__RELEASE(dst[((c * 8) + i) + 96]);
      dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__209);
      __pool__RELEASE(__tmp__198);
      __pool__RELEASE(__tmp__199);
      __pool__RELEASE(__tmp__200);
      __pool__RELEASE(__tmp__201);
      __pool__RELEASE(__tmp__202);
      __pool__RELEASE(__tmp__203);
      __pool__RELEASE(__tmp__204);
      __pool__RELEASE(__tmp__205);
      __pool__RELEASE(__tmp__206);
      __pool__RELEASE(__tmp__207);
      __pool__RELEASE(__tmp__208);
      __pool__RELEASE(__tmp__209);
    }

    i = 1;
    bit __tmp__211 = __pool__XOR(a02s[i], a02s[(1 * 8) + i]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__211);
    bit __tmp__212 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__212);
    bit __tmp__213 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
    __pool__RELEASE(dst[(c * 8) + i]);
    dst[(c * 8) + i] = __pool__COPY(__tmp__213);
    bit __tmp__214 = __pool__XOR(a02s[(2 * 8) + i], a02s[(1 * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__214);
    bit __tmp__215 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__215);
    bit __tmp__216 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
    __pool__RELEASE(dst[((c * 8) + i) + 32]);
    dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__216);
    bit __tmp__217 = __pool__XOR(a02s[(2 * 8) + i], a02s[(3 * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__217);
    bit __tmp__218 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__218);
    bit __tmp__219 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
    __pool__RELEASE(dst[((c * 8) + i) + 64]);
    dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__219);
    bit __tmp__220 = __pool__XOR(a02s[(3 * 8) + i], a02s[(0 * 8) + i]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__220);
    bit __tmp__221 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__221);
    bit __tmp__222 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
    __pool__RELEASE(dst[((c * 8) + i) + 96]);
    dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__222);
    for (i = 3; i <= 4; i++)
    {
      bit __tmp__224 = __pool__XOR(a02s[(0 * 8) + i], a02s[(1 * 8) + i]);
      __pool__RELEASE(dst[(c * 8) + i]);
      dst[(c * 8) + i] = __pool__COPY(__tmp__224);
      bit __tmp__225 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 64]);
      __pool__RELEASE(dst[(c * 8) + i]);
      dst[(c * 8) + i] = __pool__COPY(__tmp__225);
      bit __tmp__226 = __pool__XOR(dst[(c * 8) + i], src[((c * 8) + i) + 96]);
      __pool__RELEASE(dst[(c * 8) + i]);
      dst[(c * 8) + i] = __pool__COPY(__tmp__226);
      bit __tmp__227 = __pool__XOR(a02s[(2 * 8) + i], a02s[(1 * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 32]);
      dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__227);
      bit __tmp__228 = __pool__XOR(dst[((c * 8) + i) + 32], src[(c * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 32]);
      dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__228);
      bit __tmp__229 = __pool__XOR(dst[((c * 8) + i) + 32], src[((c * 8) + i) + 96]);
      __pool__RELEASE(dst[((c * 8) + i) + 32]);
      dst[((c * 8) + i) + 32] = __pool__COPY(__tmp__229);
      bit __tmp__230 = __pool__XOR(a02s[(2 * 8) + i], a02s[(3 * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 64]);
      dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__230);
      bit __tmp__231 = __pool__XOR(dst[((c * 8) + i) + 64], src[(c * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 64]);
      dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__231);
      bit __tmp__232 = __pool__XOR(dst[((c * 8) + i) + 64], src[((c * 8) + i) + 16]);
      __pool__RELEASE(dst[((c * 8) + i) + 64]);
      dst[((c * 8) + i) + 64] = __pool__COPY(__tmp__232);
      bit __tmp__233 = __pool__XOR(a02s[(3 * 8) + i], a02s[(0 * 8) + i]);
      __pool__RELEASE(dst[((c * 8) + i) + 96]);
      dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__233);
      bit __tmp__234 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 32]);
      __pool__RELEASE(dst[((c * 8) + i) + 96]);
      dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__234);
      bit __tmp__235 = __pool__XOR(dst[((c * 8) + i) + 96], src[((c * 8) + i) + 64]);
      __pool__RELEASE(dst[((c * 8) + i) + 96]);
      dst[((c * 8) + i) + 96] = __pool__COPY(__tmp__235);
      __pool__RELEASE(__tmp__224);
      __pool__RELEASE(__tmp__225);
      __pool__RELEASE(__tmp__226);
      __pool__RELEASE(__tmp__227);
      __pool__RELEASE(__tmp__228);
      __pool__RELEASE(__tmp__229);
      __pool__RELEASE(__tmp__230);
      __pool__RELEASE(__tmp__231);
      __pool__RELEASE(__tmp__232);
      __pool__RELEASE(__tmp__233);
      __pool__RELEASE(__tmp__234);
      __pool__RELEASE(__tmp__235);
    }

    __pool__RELEASE(__tmp__172);
    __pool__RELEASE(__tmp__173);
    __pool__RELEASE(__tmp__174);
    __pool__RELEASE(__tmp__175);
    __pool__RELEASE(__tmp__176);
    __pool__RELEASE(__tmp__177);
    __pool__RELEASE(__tmp__178);
    __pool__RELEASE(__tmp__179);
    __pool__RELEASE(__tmp__180);
    __pool__RELEASE(__tmp__181);
    __pool__RELEASE(__tmp__182);
    __pool__RELEASE(__tmp__183);
    __pool__RELEASE(__tmp__185);
    __pool__RELEASE(__tmp__186);
    __pool__RELEASE(__tmp__187);
    __pool__RELEASE(__tmp__188);
    __pool__RELEASE(__tmp__189);
    __pool__RELEASE(__tmp__190);
    __pool__RELEASE(__tmp__191);
    __pool__RELEASE(__tmp__192);
    __pool__RELEASE(__tmp__193);
    __pool__RELEASE(__tmp__194);
    __pool__RELEASE(__tmp__195);
    __pool__RELEASE(__tmp__196);
    __pool__RELEASE(__tmp__211);
    __pool__RELEASE(__tmp__212);
    __pool__RELEASE(__tmp__213);
    __pool__RELEASE(__tmp__214);
    __pool__RELEASE(__tmp__215);
    __pool__RELEASE(__tmp__216);
    __pool__RELEASE(__tmp__217);
    __pool__RELEASE(__tmp__218);
    __pool__RELEASE(__tmp__219);
    __pool__RELEASE(__tmp__220);
    __pool__RELEASE(__tmp__221);
    __pool__RELEASE(__tmp__222);
  }

  for (int i = 0; i < 128; i++)
  {
    __pool__RELEASE(src[i]);
    src[i] = __pool__COPY(dst[i]);
  }

  __pool__RELEASEArray(dst, 128);
  __pool__RELEASEArray(a02s, 32);
}

void RotWord(bit a[])
{
  bit tmp = __pool__NewVar();
  int i;
  int j;
  for (i = 0; i < 8; i++)
  {
    __pool__RELEASE(tmp);
    tmp = __pool__COPY(a[i]);
    for (j = 0; j < 3; j++)
    {
      __pool__RELEASE(a[(j * 8) + i]);
      a[(j * 8) + i] = __pool__COPY(a[((j * 8) + i) + 8]);
    }

    __pool__RELEASE(a[24 + i]);
    a[24 + i] = __pool__COPY(tmp);
  }

  __pool__RELEASE(tmp);
}

void Mul2(bit b[])
{
  bit tmp = __pool__NewVar();
  __pool__RELEASE(tmp);
  tmp = __pool__COPY(b[7]);
  __pool__RELEASE(b[7]);
  b[7] = __pool__COPY(b[6]);
  __pool__RELEASE(b[6]);
  b[6] = __pool__COPY(b[5]);
  __pool__RELEASE(b[5]);
  b[5] = __pool__COPY(b[4]);
  bit __tmp__249 = __pool__XOR(b[3], tmp);
  __pool__RELEASE(b[4]);
  b[4] = __pool__COPY(__tmp__249);
  bit __tmp__250 = __pool__XOR(b[2], tmp);
  __pool__RELEASE(b[3]);
  b[3] = __pool__COPY(__tmp__250);
  __pool__RELEASE(b[2]);
  b[2] = __pool__COPY(b[1]);
  bit __tmp__252 = __pool__XOR(b[0], tmp);
  __pool__RELEASE(b[1]);
  b[1] = __pool__COPY(__tmp__252);
  __pool__RELEASE(b[0]);
  b[0] = __pool__COPY(tmp);
  __pool__RELEASE(tmp);
  __pool__RELEASE(__tmp__249);
  __pool__RELEASE(__tmp__250);
  __pool__RELEASE(__tmp__252);
}

void KEYEXPENSION(bit AESROUNDKEY[], bit AESKEY[])
{
  bit Rcon[8]; __pool__NewArray(Rcon, 8);
  bit tmp[32]; __pool__NewArray(tmp, 32);
  bit tmps[8]; __pool__NewArray(tmps, 8);
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
    __pool__RELEASE(AESROUNDKEY[i]);
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
      __pool__RELEASE(AESROUNDKEY[(i * 32) + j]);
      AESROUNDKEY[(i * 32) + j] = __pool__XOR(AESROUNDKEY[((i * 32) + j) - 128], tmp[j]);
    }

  }

  __pool__RELEASEArray(Rcon, 8);
  __pool__RELEASEArray(tmp, 32);
  __pool__RELEASEArray(tmps, 8);
}

void AddRoundKey(Index ROUNDKEY[], Index MSG[], int round)
{
  int i;
  for (i = 0; i < 128; i++)
  {
    bit __tmp__273 = __pool__XOR(MSG[i], ROUNDKEY[(128 * round) + i]);
    __pool__RELEASE(MSG[i]);
    MSG[i] = __pool__COPY(__tmp__273);
    __pool__RELEASE(__tmp__273);
  }

}

void SubBytes(Index MSG[])
{
  int i = 0;
  for (i = 0; i < 16; i++)
  {
    GFINV(&MSG[i * 8]);
  }

}

void AES(bit *input)
{
  int i;
  bit AESROUNDKEY[1408]; __pool__NewArray(AESROUNDKEY, 1408);
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

