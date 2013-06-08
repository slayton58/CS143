class T0
{
f0 : Int <- 37;
f1 : Int <- 937;
f2 : Int <- 45;
f3 : Bool <- false;
m77(a78 : T1, a79 : Int, a80 : Int, a81 : Int) : T7
{
let l155 : T0 <- a78 in 
( new T7) 

};
m82() : T1
{
( new T1) 

};
m83(a84 : T8, a85 : T0, a86 : Int) : T7
{
( new T7) 

};
m87(a88 : T3, a89 : T8, a90 : T1) : T8
{
a89
};

};
class T1 inherits T0
{
f4 : String <- new String;
f5 : Int <- 173;
f6 : Bool <- false;
m97(a98 : T5) : Int
{
~(f5)
};
m82() : T1
{
( new T3) 

};
m87(a88 : T3, a89 : T8, a90 : T1) : T8
{
a89
};
m91(a92 : T7, a93 : Int, a94 : T7, a95 : Int, a96 : Int) : T2
{
( new T2) 

};

};
class T2
{
f10 : Bool <- true;
f11 : String <- new String;
f12 : Bool <- true;
f13 : Bool <- true;
f14 : Bool <- false;
f7 : Int <- 529;
f8 : Int <- 939;
f9 : Int <- 291;
m99(a100 : T1, a101 : String, a102 : T1) : Int
{
((f8+(((f9*f7)*(f9+f9))*((f9 <- f9)
*let l156 : T1 <- a102,
l157 : Int <- f9 in 
f9)))+(f8*(f8+((f7*f7)*~(f8)))))
};
m103() : T2
{
 if f14 then ( new T2) 
 else ( new T2) 
 fi 
};
m104(a105 : Bool, a106 : T5, a107 : Int) : T5
{
a106
};

};
class T3 inherits T1
{
f15 : Bool <- true;
f16 : String <- new String;
f17 : Bool <- true;
f18 : Bool <- true;
f19 : String <- new String;
f20 : String <- new String;
f21 : Bool <- true;
f22 : String <- new String;
f23 : Int <- 721;
f24 : Int <- 568;
f25 : String <- new String;
f26 : Int <- 788;
f27 : Bool <- false;
f28 : Int <- 98;
f29 : Bool <- true;
f30 : String <- new String;
f31 : Bool <- true;
f32 : Bool <- false;
m82() : T1
{
( new T3) 

};
m91(a92 : T7, a93 : Int, a94 : T7, a95 : Int, a96 : Int) : T2
{
( new T2) 

};
m115() : T3
{
( new T3) 

};
m108(a109 : Bool, a110 : T2, a111 : Int, a112 : Int, a113 : Int) : Int
{
~((f0+((a113+(f5 <- a113)
)*(f2 <- (a112+f24))
)))
};
m114() : Bool
{
f3=f17
};
m116() : T1
{
( new T1) 

};

};
class T4 inherits T0
{
f33 : Bool <- true;
f34 : Bool <- false;
f35 : Int <- 651;
f36 : Int <- 332;
f37 : Int <- 235;
f38 : Bool <- false;
f39 : Int <- 790;
f40 : Bool <- true;
f41 : Int <- 565;
f42 : Int <- 605;
f43 : Int <- 578;
f44 : Int <- 946;
f45 : Bool <- false;
f46 : String <- new String;
f47 : Bool <- true;
f48 : Int <- 720;
f49 : Bool <- true;
f50 : Int <- 396;
f51 : Bool <- false;
m82() : T1
{
( new T1) 

};
m83(a84 : T8, a85 : T0, a86 : Int) : T7
{
( new T7) 

};
m117(a118 : T1, a119 : T1, a120 : T3) : T5
{
( new T5) 

};
m121() : Int
{
 if ((f1 <- f50)
*(f2+case f43 of 
c158 : Int => f2;
c159 : T2 => f39;
c160 : T3 => f43;

esac
))<f44 then f0 else (f35 <- f41)
 fi 
};

};
class T5 inherits T0
{
f52 : Bool <- true;
f53 : Int <- 957;
f54 : Bool <- true;
f55 : Bool <- true;
f56 : Int <- 501;
f57 : Bool <- true;
f58 : Bool <- true;
f59 : Int <- 164;
f60 : Int <- 214;
f61 : Bool <- false;
m82() : T1
{
( new T3) 

};
m122(a123 : Bool) : Int
{
(((f1+((f59*f56)*(f2*f1)))*((f1 <- f60)
+((f53*f53)*(f2*f59))))+f56)
};
m124(a125 : Bool, a126 : T2) : Bool
{
(~(((f56 <- f2)
*~(f0)))*~((~(f53)*let l161 : T7 <- ( new T7) 
 in 
f56)))<~((f60*(let l162 : Int <- f56 in 
f1*f60)))
};

};
class T6 inherits T0
{
f62 : Int <- 982;
f63 : Int <- 214;
f64 : Bool <- true;
f65 : Int <- 589;
f66 : Int <- 442;
f67 : Int <- 736;
f68 : Int <- 78;
f69 : Bool <- true;
f70 : Bool <- true;
f71 : Bool <- false;
m77(a78 : T1, a79 : Int, a80 : Int, a81 : Int) : T7
{
m83(( new T8) 
, a78, ((case case f68 of 
c163 : Int => a79;
c164 : T3 => f68;
c165 : String => a79;

esac
 of 
c166 : Int => (f67*f0);
c167 : T8 => case ( new T2) 
 of 
c168 : T2 => f67;
c169 : T5 => a79;
c170 : T0 => a81;

esac
;

esac
+(f65 <- (a81+f62))
)+f66))

};
m82() : T1
{
( new T1) 

};
m83(a84 : T8, a85 : T0, a86 : Int) : T7
{
( new T7) 

};

};
class T7 inherits T6
{
f72 : Bool <- true;
f73 : Int <- 768;
f74 : Int <- 774;
m87(a88 : T3, a89 : T8, a90 : T1) : T8
{
a89
};
m127(a128 : Int, a129 : Int, a130 : Int, a131 : T8, a132 : T8, a133 : T7, a134 : Int) : Int
{
((((case a133 of 
c171 : T0 => f73;
c172 : Int => f63;

esac
*(f74 <- a134)
)*~((f0*f0)))+a132.m146(case (a129*f62) of 
c173 : Int => let l174 : T8 <- a131,
l175 : Int <- f63 in 
( new T3) 
;
c176 : T6 => ( new T3) 
;
c177 : String => ( new T3) 
;

esac
, ( new T3) 
, ( new T4) 
,  if f72=f64 then (a129*f2) else ~(f2) fi , ( new T3) 
, a132)
)+(f2+f66))
};

};
class T8
{
f75 : Bool <- false;
f76 : Int <- 839;
m135(a136 : Int, a137 : Int, a138 : T2, a139 : T5) : T2
{
a138
};
m140(a141 : Int, a142 : T1, a143 : T1, a144 : Int, a145 : T7) : Bool
{
f75
};
m146(a147 : T3, a148 : T3, a149 : T4, a150 : Int, a151 : T3, a152 : T8) : Int
{
(a150*a150)
};
m153(a154 : Bool) : T7
{
( new T7) 

};

};
Class Main inherits IO {
vT0 : T0 <- (new T0) ;
vT1 : T1 <- (new T1) ;
vT2 : T2 <- (new T2) ;
vT3 : T3 <- (new T3) ;
vT4 : T4 <- (new T4) ;
vT5 : T5 <- (new T5) ;
vT6 : T6 <- (new T6) ;
vT7 : T7 <- (new T7) ;
vT8 : T8 <- (new T8) ;
main() : Int { {
out_string("vT0.m77\n");
vT0.m77(vT1, ((((let l178 : T3 <- vT3 in 
 853 +( 665 * 551 ))+ 119 )+case (~( 9 )* 398 ) of 
c179 : Int => (~(c179)+(c179+c179));
c180 : T2 => ~( 694 );
c181 : T7 => (let l182 : Bool <- false,
l183 : String <-  "s1484001214"  in 
 456 + 31 );

esac
)*(( 54 +( 323 +( 457 + 589 )))+(~(( 178 + 963 ))* 670 ))), case ~((~( 966 )*~( 910 )))= 177  of 
c184 : Bool => ( 401 + 217 );
c185 : String => (~(vT4.m121() )*~( 431 ));
c186 : T1 =>  751 ;

esac
,  593 )
;
out_string("vT0.m82\n");
vT0.m82() ;
out_string("vT0.m83\n");
vT0.m83( if case ( 879 * 344 ) of 
c187 : Int => c187;
c188 : T8 => (case c188 of 
c189 : T8 =>  388 ;
c190 : T3 =>  764 ;

esac
* 972 );

esac
<=( 919 +~(let l191 : Int <-  461  in 
l191)) then vT0.m87(vT3, let l192 : String <-  "s2011116321"  in 
vT0.m87(vT3, vT7.m87(vT3, vT8, vT3)
, vT3)
, (vT3 <- vT3)
)
 else vT8 fi , vT6, ( 93 * 376 ))
;
out_string("vT0.m87\n");
vT0.m87(vT3, vT8, vT0.m82() )
;
out_string("vT1.m97\n");
out_int(vT1.m97(let l193 : String <- case vT0.m83(vT8, vT0.m77(case  385  of 
c194 : Int => vT1;
c195 : T3 => vT3;
c196 : T7 => vT1;

esac
,  287 , ( 509 + 645 ), ( 793 + 211 ))
,  448 )
 of 
c197 : T6 =>  "s236027331" ;
c198 : Int => case let l199 : Int <- ~(c198) in 
true=false of 
c200 : Bool =>  "s738993194" ;
c201 : Int =>  "s548199926" ;

esac
;

esac
 in 
case case vT0.m77((vT3 <- vT3)
, case true of 
c202 : Bool =>  270 ;

esac
,  287 , ( 380 * 808 ))
 of 
c203 : T7 => vT8;

esac
 of 
c204 : T8 => vT5;
c205 : T4 => vT5;

esac
)
);out_string("\n");
out_string("vT1.m82\n");
vT1.m82() ;
out_string("vT1.m87\n");
vT1.m87(vT3, vT8, case vT3 of 
c206 : T3 => vT3;
c207 : T8 => (vT3 <- vT3.m115() )
;
c208 : T2 => (vT3 <- vT3)
;

esac
)
;
out_string("vT1.m91\n");
vT1.m91(vT7, ~(~( 321 )), vT7, ~( 834 ),  880 )
;
out_string("vT2.m99\n");
out_int(vT2.m99(case case case let l209 : Int <- case vT2 of 
c210 : T2 =>  596 ;
c211 : Int => c211;
c212 : T1 =>  725 ;

esac
,
l213 : T6 <- case  "s881861532"  of 
c214 : String => vT7;
c215 : Int => vT7;
c216 : T8 => vT7;

esac
 in 
case vT5 of 
c217 : T5 => l209;

esac
 of 
c218 : Int => case  "s1107182519"  of 
c219 : String => c219;
c220 : Int =>  "s76265050" ;
c221 : Bool =>  "s1266562742" ;

esac
;
c222 : T3 =>  "s908330237" ;

esac
 of 
c223 : String => (( 298 *case vT7 of 
c224 : T7 =>  466 ;
c225 : T6 =>  119 ;
c226 : Bool =>  102 ;

esac
)+(( 959 + 320 )+ 183 ));
c227 : T1 => case vT3 of 
c228 : T3 => ( if false then  381  else  741  fi *case vT4 of 
c229 : T4 =>  478 ;
c230 : Bool =>  740 ;
c231 : T3 =>  168 ;

esac
);
c232 : Int => c232;
c233 : T8 => ( 329 *~( 264 ));

esac
;
c234 : Int => c234;

esac
 of 
c235 : Int => (vT3 <- case (vT3 <- vT3)
 of 
c236 : T1 => vT3.m115() ;
c237 : Int => let l238 : String <-  "s1365812749" ,
l239 : T4 <- vT4 in 
vT3;

esac
)
;

esac
,  "s603321706" , vT3)
);out_string("\n");
out_string("vT2.m103\n");
vT2.m103() ;
out_string("vT2.m104\n");
vT2.m104(vT3.m114() , let l240 : T5 <- case true of 
c241 : Bool => vT5;
c242 : Int => vT2.m104(let l243 : T1 <- vT1 in 
false, vT5, let l244 : T3 <- vT3,
l245 : Int <- (c242+c242) in 
(c242*l245))
;
c246 : T7 => vT4.m117(vT3, let l247 : Int <- case vT3 of 
c248 : T1 =>  54 ;

esac
,
l249 : Int <- l247 in 
vT1, vT3)
;

esac
,
l250 : Int <- ((let l251 : T0 <- vT0 in 
l240.m122(false)
*(( 338 + 129 )+~( 298 )))+vT2.m99(vT3,  "s1350343096" , let l252 : Bool <- false in 
case vT2 of 
c253 : T2 => vT1;

esac
)
) in 
vT5,  if true then vT8.m146(vT3, case vT4 of 
c254 : T0 => vT3;

esac
, case (vT3 <- case vT8 of 
c255 : T8 => vT3;
c256 : Int => vT3;

esac
)
 of 
c257 : T1 => vT4;

esac
, ~(~(( 47 * 239 ))), vT3, vT8)
 else  152  fi )
;
out_string("vT3.m82\n");
vT3.m82() ;
out_string("vT3.m91\n");
vT3.m91(vT7, ~(((( 231 *( 416 + 264 ))+ 80 )* 371 )), let l258 : T2 <- let l259 : T8 <- case false of 
c260 : Bool => vT8;
c261 : T2 => vT0.m87(vT3, vT8, case c261 of 
c262 : T2 => vT1;
c263 : T0 => vT1;

esac
)
;

esac
 in 
vT2,
l264 : T1 <- case ~(case  "s1401221488"  of 
c265 : String =>  281 ;

esac
) of 
c266 : Int => let l267 : T1 <- vT3 in 
case  "s721122867"  of 
c268 : String => vT1.m82() ;
c269 : Bool => (vT3 <- vT3)
;
c270 : T8 => l267.m82() ;

esac
;

esac
 in 
vT7, ~( 817 ),  904 )
;
out_string("vT3.m115\n");
vT3.m115() ;
out_string("vT3.m108\n");
out_int(vT3.m108(let l271 : T8 <- vT8,
l272 : T3 <- vT3 in 
( 928 * 887 )<= 114 , vT2, case vT2 of 
c273 : T2 =>  754 ;

esac
, let l274 : T6 <- (vT7 <- vT0.m77(let l275 : T3 <- vT3.m115()  in 
(vT3 <- l275)
, ~( 421 ), ( 552 * 68 ),  592 )
)
,
l276 : T5 <- vT5 in 
 642 , ~((((( 714 * 5 )* 396 )*(~( 267 )* 233 ))*~(vT8.m146(vT3, case  434  of 
c277 : Int => vT3;
c278 : T5 => vT3;
c279 : T3 => c279;

esac
, vT4, ( 351 + 823 ), vT3, vT8)
))))
);out_string("\n");
out_string("vT3.m114\n");
vT3.m114() ;
out_string("vT3.m116\n");
vT3.m116() ;
out_string("vT4.m82\n");
vT4.m82() ;
out_string("vT4.m83\n");
vT4.m83(case vT5 of 
c280 : T5 => vT8;
c281 : Int => vT8;
c282 : Bool => vT8;

esac
, let l283 : Int <-  87 ,
l284 : String <- let l285 : T1 <- (vT3 <- vT3)
 in 
 "s744395299"  in 
(vT7 <- vT7)
, case vT7 of 
c286 : T0 => vT5.m122(false)
;

esac
)
;
out_string("vT4.m117\n");
vT4.m117(vT3, vT3,  if  781 <((case vT7 of 
c287 : T7 =>  520 ;
c288 : Int => c288;
c289 : T6 =>  222 ;

esac
+( 334 * 879 ))*vT4.m121() ) then vT3 else vT3 fi )
;
out_string("vT4.m121\n");
out_int(vT4.m121() );out_string("\n");
out_string("vT5.m82\n");
vT5.m82() ;
out_string("vT5.m122\n");
out_int(vT5.m122(case  697  of 
c290 : Int => let l291 : Bool <- c290<=c290 in 
 if l291 then case case vT3 of 
c292 : T3 => vT2;
c293 : T7 => vT2;

esac
 of 
c294 : T2 => l291;
c295 : Int => case vT6 of 
c296 : T6 => l291;
c297 : T5 => l291;

esac
;

esac
 else l291 fi ;
c298 : T6 => false;

esac
)
);out_string("\n");
out_string("vT5.m124\n");
vT5.m124(case let l299 : Bool <- (~( 883 )* 993 )<let l300 : T1 <- (vT3 <- vT3)
 in 
case true of 
c301 : Bool =>  760 ;

esac
 in 
( 49 *~(~( 396 ))) of 
c302 : Int => true;
c303 : T4 => true;

esac
, vT1.m91(vT7, ~(( 422 + 800 )), case let l304 : T4 <- vT4,
l305 : String <- case  if false then vT6 else vT6 fi  of 
c306 : T6 => let l307 : Int <-  969  in 
 "s1358680402" ;

esac
 in 
~( 840 )< 685  of 
c308 : Bool => let l309 : T0 <- case vT3 of 
c310 : T3 => case c308 of 
c311 : Bool => vT0;
c312 : T0 => vT6;

esac
;
c313 : Bool => vT4;
c314 : T8 => vT8.m153(c308)
;

esac
,
l315 : Int <- (~( 515 )*case vT7 of 
c316 : T7 =>  82 ;
c317 : Int => c317;
c318 : String =>  856 ;

esac
) in 
l309.m83(vT8,  if c308 then vT1 else vT3 fi , (l315*l315))
;
c319 : T2 => vT7;

esac
, (case  735  of 
c320 : Int => c320;
c321 : T1 =>  81 ;

esac
+( 667 +(let l322 : Int <-  803 ,
l323 : T3 <- vT3 in 
l322+( 213 * 646 )))),  703 )
)
;
out_string("vT6.m77\n");
vT6.m77(vT1,  766 , ( 880 *vT8.m146(vT3, vT3, vT4, ( 818 *~(( 97 + 732 ))), vT3, vT8)
), ( 926 +((~(( 22 * 763 ))*let l324 : Int <- ( 885 * 716 ) in 
(l324*l324))+(vT1.m97(vT5)
*vT2.m99(vT3,  "s1206369208" , vT0.m82() )
))))
;
out_string("vT6.m82\n");
vT6.m82() ;
out_string("vT6.m83\n");
vT6.m83(vT8, vT7,  330 )
;
out_string("vT7.m87\n");
vT7.m87(vT3, vT8, vT1.m82() )
;
out_string("vT7.m127\n");
out_int(vT7.m127( 800 ,  42 , ~(( 229 * 883 )), vT8, vT0.m87(vT3, let l325 : Int <- ~(( 470 *( 260 + 448 ))) in 
vT8, (vT3 <- vT3)
)
, vT7,  177 )
);out_string("\n");
out_string("vT8.m135\n");
vT8.m135( 788 , case vT5 of 
c326 : T5 => ( 107 * 889 );

esac
, vT2, vT5)
;
out_string("vT8.m140\n");
vT8.m140(case (vT3 <- vT3)
 of 
c327 : T1 => vT8.m146(vT3, vT3, let l328 : T0 <- vT4 in 
 if false then vT4 else vT4 fi , (~(~( 117 ))+~( 422 )), case  849  of 
c329 : Int => case ~(c329) of 
c330 : Int => let l331 : T3 <- vT3 in 
vT3;

esac
;
c332 : T8 => let l333 : Int <- ~( 332 ),
l334 : T6 <- let l335 : Int <- l333,
l336 : Bool <- false in 
vT6 in 
vT3.m115() ;

esac
, vT8)
;

esac
, vT3, (vT3 <- vT3)
, vT8.m146(vT3, vT3, vT4,  102 , vT3, case vT3.m91(vT7, (( 663 * 740 )*( 587 + 301 )), case vT4.m117(vT3, vT3, vT3)
 of 
c337 : T5 => case false of 
c338 : Bool => vT7;
c339 : Int => vT7;

esac
;

esac
,  978 , ~( if false then  270  else  56  fi ))
 of 
c340 : T2 => case (vT3 <- let l341 : Int <-  18 ,
l342 : T1 <- vT1 in 
vT3)
 of 
c343 : T1 => vT0.m87(vT3, let l344 : Int <-  562 ,
l345 : T0 <- vT1 in 
vT8, (vT3 <- vT3)
)
;
c346 : T7 => vT8;

esac
;
c347 : Int => vT8;
c348 : T8 => case case vT7 of 
c349 : T7 => case vT3 of 
c350 : T1 => vT3;

esac
;
c351 : T8 => let l352 : T0 <- vT5,
l353 : Int <-  5  in 
vT3;
c354 : T2 => vT3;

esac
 of 
c355 : T3 => c348;

esac
;

esac
)
, vT7)
;
out_string("vT8.m146\n");
out_int(vT8.m146(vT3, case (case vT3.m115()  of 
c356 : T3 => ~(~( 874 ));
c357 : Int => ~(c357);
c358 : T4 => ~(( 386 * 439 ));

esac
+(let l359 : T0 <- (vT7 <- vT7)
 in 
~( 19 )*~(( 535 + 754 )))) of 
c360 : Int => vT3;
c361 : T7 => vT3.m115() ;
c362 : T6 => case vT3 of 
c363 : T1 => let l364 : T4 <- vT4,
l365 : T5 <- vT2.m104(false, vT4.m117(c363, c363, vT3)
, ~( 697 ))
 in 
vT3;
c366 : Int => vT3;
c367 : String => vT3;

esac
;

esac
, let l368 : T3 <- vT3.m115()  in 
vT4,  278 , vT3.m115() , vT1.m87(case ( 20 +(~( 798 )+~( 705 ))) of 
c369 : Int => vT3;

esac
, vT8, (vT3 <- vT3)
)
)
);out_string("\n");
out_string("vT8.m153\n");
vT8.m153(( 153 *~((vT5.m122(true)
* 87 )))=vT8.m146(case  189  of 
c370 : Int =>  if true then vT3 else case c370 of 
c371 : Int => vT3;
c372 : String => vT3;

esac
 fi ;
c373 : T8 => vT3;
c374 : T6 => vT3;

esac
, vT3, case vT8 of 
c375 : T8 => vT4;
c376 : T0 => vT4;
c377 : T3 => vT4;

esac
, ~( 834 ), vT3, case vT4 of 
c378 : T4 => let l379 : T8 <- vT8,
l380 : Bool <- true in 
l379;

esac
)
)
;
 0; }
};
};