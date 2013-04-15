(*****************************************************
 *
 *                 Unit Test section
 * Here we exercise the lexer on basic units in Cool manual
 *
 *****************************************************)

(* Integer *)
0 1 1234567890 ~1234567890 123-321
000123
2147483647
2147483648
4294967295
4294967296
9999999999999999999999999999999999999999999999999999999999999999999999
10000000000000000000000000000000000000000000000000000000000000000000000

(* Identifiers *)
Identifiers             identifiers
I_dentifier_0123_abcd   i_dentifier_0123_abcd
If12then                if12then
self                    SELF
SELF_TYPE               self_type

(* Operators *)
{ + - * / ~ < <= = <- ; }

(* Keywords *)
true tRue trUe tRUe truE tRuE trUE tRUE 
false fAlse faLse fALse falSe fAlSe faLSe fALSe falsE fAlsE faLsE fALsE falSE fAlSE faLSE fALSE 
class Class cLass CLass clAss ClAss cLAss CLAss claSs ClaSs cLaSs CLaSs clASs ClASs cLASs CLASs clasS ClasS cLasS CLasS clAsS ClAsS cLAsS CLAsS claSS ClaSS cLaSS CLaSS clASS ClASS cLASS CLASS 
else Else eLse ELse elSe ElSe eLSe ELSe elsE ElsE eLsE ELsE elSE ElSE eLSE ELSE 
fi Fi fI FI 
if If iF IF 
in In iN IN 
inherits Inherits iNherits INherits inHerits InHerits iNHerits INHerits inhErits InhErits iNhErits INhErits inHErits InHErits iNHErits INHErits inheRits InheRits iNheRits INheRits inHeRits InHeRits iNHeRits INHeRits inhERits InhERits iNhERits INhERits inHERits InHERits iNHERits INHERits inherIts InherIts iNherIts INherIts inHerIts InHerIts iNHerIts INHerIts inhErIts InhErIts iNhErIts INhErIts inHErIts InHErIts iNHErIts INHErIts inheRIts InheRIts iNheRIts INheRIts inHeRIts InHeRIts iNHeRIts INHeRIts inhERIts InhERIts iNhERIts INhERIts inHERIts InHERIts iNHERIts INHERIts inheriTs InheriTs iNheriTs INheriTs inHeriTs InHeriTs iNHeriTs INHeriTs inhEriTs InhEriTs iNhEriTs INhEriTs inHEriTs InHEriTs iNHEriTs INHEriTs inheRiTs InheRiTs iNheRiTs INheRiTs inHeRiTs InHeRiTs iNHeRiTs INHeRiTs inhERiTs InhERiTs iNhERiTs INhERiTs inHERiTs InHERiTs iNHERiTs INHERiTs inherITs InherITs iNherITs INherITs inHerITs InHerITs iNHerITs INHerITs inhErITs InhErITs iNhErITs INhErITs inHErITs InHErITs iNHErITs INHErITs inheRITs InheRITs iNheRITs INheRITs inHeRITs InHeRITs iNHeRITs INHeRITs inhERITs InhERITs iNhERITs INhERITs inHERITs InHERITs iNHERITs INHERITs inheritS InheritS iNheritS INheritS inHeritS InHeritS iNHeritS INHeritS inhEritS InhEritS iNhEritS INhEritS inHEritS InHEritS iNHEritS INHEritS inheRitS InheRitS iNheRitS INheRitS inHeRitS InHeRitS iNHeRitS INHeRitS inhERitS InhERitS iNhERitS INhERitS inHERitS InHERitS iNHERitS INHERitS inherItS InherItS iNherItS INherItS inHerItS InHerItS iNHerItS INHerItS inhErItS InhErItS iNhErItS INhErItS inHErItS InHErItS iNHErItS INHErItS inheRItS InheRItS iNheRItS INheRItS inHeRItS InHeRItS iNHeRItS INHeRItS inhERItS InhERItS iNhERItS INhERItS inHERItS InHERItS iNHERItS INHERItS inheriTS InheriTS iNheriTS INheriTS inHeriTS InHeriTS iNHeriTS INHeriTS inhEriTS InhEriTS iNhEriTS INhEriTS inHEriTS InHEriTS iNHEriTS INHEriTS inheRiTS InheRiTS iNheRiTS INheRiTS inHeRiTS InHeRiTS iNHeRiTS INHeRiTS inhERiTS InhERiTS iNhERiTS INhERiTS inHERiTS InHERiTS iNHERiTS INHERiTS inherITS InherITS iNherITS INherITS inHerITS InHerITS iNHerITS INHerITS inhErITS InhErITS iNhErITS INhErITS inHErITS InHErITS iNHErITS INHErITS inheRITS InheRITS iNheRITS INheRITS inHeRITS InHeRITS iNHeRITS INHeRITS inhERITS InhERITS iNhERITS INhERITS inHERITS InHERITS iNHERITS INHERITS 
isvoid Isvoid iSvoid ISvoid isVoid IsVoid iSVoid ISVoid isvOid IsvOid iSvOid ISvOid isVOid IsVOid iSVOid ISVOid isvoId IsvoId iSvoId ISvoId isVoId IsVoId iSVoId ISVoId isvOId IsvOId iSvOId ISvOId isVOId IsVOId iSVOId ISVOId isvoiD IsvoiD iSvoiD ISvoiD isVoiD IsVoiD iSVoiD ISVoiD isvOiD IsvOiD iSvOiD ISvOiD isVOiD IsVOiD iSVOiD ISVOiD isvoID IsvoID iSvoID ISvoID isVoID IsVoID iSVoID ISVoID isvOID IsvOID iSvOID ISvOID isVOID IsVOID iSVOID ISVOID 
let Let lEt LEt leT LeT lET LET 
loop Loop lOop LOop loOp LoOp lOOp LOOp looP LooP lOoP LOoP loOP LoOP lOOP LOOP 
pool Pool pOol POol poOl PoOl pOOl POOl pooL PooL pOoL POoL poOL PoOL pOOL POOL 
then Then tHen THen thEn ThEn tHEn THEn theN TheN tHeN THeN thEN ThEN tHEN THEN 
while While wHile WHile whIle WhIle wHIle WHIle whiLe WhiLe wHiLe WHiLe whILe WhILe wHILe WHILe whilE WhilE wHilE WHilE whIlE WhIlE wHIlE WHIlE whiLE WhiLE wHiLE WHiLE whILE WhILE wHILE WHILE 
case Case cAse CAse caSe CaSe cASe CASe casE CasE cAsE CAsE caSE CaSE cASE CASE 
esac Esac eSac ESac esAc EsAc eSAc ESAc esaC EsaC eSaC ESaC esAC EsAC eSAC ESAC 
new New nEw NEw neW NeW nEW NEW 
of Of oF OF 
not Not nOt NOt noT NoT nOT NOT 

(* Comments *)
(* this 
is one *)
(* this 
        is one *)
(* *)
(*
*)
(*( *)
(*)*)
(*()*)
(* level 1 (* level 2(*(**)*)*) *)
(* level 1 
(* level 2(*(**)*)*) *)
-- a valid comment
-- also (* valid --
-- also valid *)
--- also valid
(**)

(* String constants *)
"      X   "
" this is ok "
" this should also be \
  ok"
"\"this is ok\""
""
"hello\nworld"
"\c"
"\\\ "
"\\\""
" \"\
 end"
"\""
"\t"
"\\t"
"\"\"\""
"\\\\"
"\\"
"\"\\"
"\\\
  \\"
"\\ \
  \\ \""
"/"
"what if we have null?"
"\e\s\c\a\p\e is working?"

(*****************************************************
 *
 *                 Integral Test section
 * Here we test the lexer on a full-fleged Cool source code
 *
 *****************************************************)

(* models one-dimensional cellular automaton on a circle of finite radius
   arrays are faked as Strings,
   X's respresent live cells, dots represent dead cells,
   no error checking is done *)
class CellularAutomaton inherits IO {
    population_map : String;
   
    init(map : String) : SELF_TYPE {
        {
            population_map <- map;
            self;
        }
    };
   
    print() : SELF_TYPE {
        {
            out_string(population_map.concat("\n"));
            self;
        }
    };
   
    num_cells() : Int {
        population_map.length()
    };
   
    cell(position : Int) : String {
        population_map.substr(position, 1)
    };
   
    cell_left_neighbor(position : Int) : String {
        if position = 0 then
            cell(num_cells() - 1)
        else
            cell(position - 1)
        fi
    };
   
    cell_right_neighbor(position : Int) : String {
        if position = num_cells() - 1 then
            cell(0)
        else
            cell(position + 1)
        fi
    };
   
    (* a cell will live if exactly 1 of itself and it's immediate
       neighbors are alive *)
    cell_at_next_evolution(position : Int) : String {
        if (if cell(position) = "X" then 1 else 0 fi
            + if cell_left_neighbor(position) = "X" then 1 else 0 fi
            + if cell_right_neighbor(position) = "X" then 1 else 0 fi
            = 1)
        then
            "X"
        else
            '.'
        fi
    };
   
    evolve() : SELF_TYPE {
        (let position : Int in
        (let num : Int <- num_cells[] in
        (let temp : String in
            {
                while position < num loop
                    {
                        temp <- temp.concat(cell_at_next_evolution(position));
                        position <- position + 1;
                    }
                pool;
                population_map <- temp;
                self;
            }
        ) ) )
    };
};

class Main {
    cells : CellularAutomaton;
   
    main() : SELF_TYPE {
        {
            cells <- (new CellularAutomaton).init("         X         ");
            cells.print();
            (let countdown : Int <- 20 in
                while countdown > 0 loop
                    {
                        cells.evolve();
                        cells.print();
                        countdown <- countdown - 1;
                    
                pool
            );
            self;
        }
    };
};


(*****************************************************
 *
 *                   Corner cases
 *
 *****************************************************)

"hello\
-- world"

(* combination " abc \""*)
" combination (**) "
"\\\"
"try this invalid one \\\"
"try another
invalid one
"

"valid line\
invalid line
valid line\
invalid line
"

"\
\
\
\
"
"contains null  "
" recovered "
 
"recovered after a null in source code"
"recovered after an EOF"
"null at 1023"
"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901 34567890123456789012345678901234567890123456789012345678901234567890123456789"
"null at 1024"
"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012 4567890123456789012345678901234567890123456789012345678901234567890123456789"
"null at 1025"
"0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123 567890123456789012345678901234567890123456789012345678901234567890123456789"
"null at 1026"
"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234 67890123456789012345678901234567890123456789012345678901234567890123456789"

"1024 escaped char"
"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"

"1025 escaped char"
"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"

then
th en

"\f\b\n\t\a\b\c\d\e"

(* now this is bad*) *)
"still work 1?"
(***)
"still work 2?"
(* **)
"still work 3?"
(*) **)
"still work 4?"
(** *)
"still work 5?"
(* (
*)
"still work 6?"
(*((**)
"still work 7?"

"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
"recovered after the too-long string"

(* one comment end with EOF
