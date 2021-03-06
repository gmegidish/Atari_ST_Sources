IMPLEMENTATION MODULE AESGraphics;
(*$L-, N+, Y+*)


(*  MEGAMAX MODULA 2 GEM-Library :  Die AES Grafikfunktionen
 *
 *  Autor: Manuel Chakravarty           Erstellt :  05.11.87
 *
 *  Version   2.2     V#0015
 *)
 
(*  05.11.87    | �bernahme von 'GEMBase' und 'GEMExt'
 *  15.02.90    | Anpassung an Compilerversion 4.0
 *  02.04.90    | Anpassung an public arrays
 *)


FROM    SYSTEM          IMPORT ASSEMBLER;

FROM    GrafBase        IMPORT Point, Rectangle, PtrMouseFormDef;

FROM    GEMGlobals      IMPORT MButtonSet, SpecialKeySet, OStateSet, PtrObjTree;
 
IMPORT  GEMShare;

(*$I GEMOPS.ICL *)
 
 
PROCEDURE GrafMouse (form: MouseForm; mFormDefPtr: PtrMouseFormDef);

  BEGIN
        ASSEMBLER
          JMP         grafMouse       ; Zur eigentlichen Routine
        END;
  END GrafMouse;

PROCEDURE MouseKeyState (VAR mouseLoc : Point;
                         VAR mouseButs: MButtonSet;
                         VAR keys     : SpecialKeySet);
                        
  BEGIN
    ASSEMBLER
        MOVE.W  #GRAF_MKSTATE,(A3)+
        JSR     aes_if
        MOVE.L  pubs,A0
        LEA     pubArrays.aINTOUT+10(A0),A0
        MOVE.L  -(A3),A1
        MOVE.W  -(A0),D0
        MOVE.B  D0,(A1)
        MOVE.L  -(A3),A1
        MOVE.W  -(A0),D0
        MOVE.B  D0,(A1)
        MOVE.L  -(A3),A1
        MOVE.L  -(A0),(A1)
    END;
  END MouseKeyState;
      
PROCEDURE MoveBox(orgin:Rectangle;dest:Point);
  
BEGIN
  ASSEMBLER
    MOVE.L      pubs,A0
    LEA         pubArrays.aINTIN(A0),A0
    MOVE.W      -(A3),$A(A0)
    MOVE.W      -(A3),$8(A0)
    MOVE.W      -(A3),$2(A0)
    MOVE.W      -(A3),(A0)
    MOVE.W      -(A3),$6(A0)
    MOVE.W      -(A3),$4(A0)
    MOVE.W      #GRAF_MBOX,(A3)+
    JSR         aes_if
    JSR         testINTOUT0
  END;
END MoveBox;

PROCEDURE GrowBox(orgin,dest:Rectangle);

BEGIN
  ASSEMBLER
    MOVE.L      pubs,A0
    LEA         pubArrays.aINTIN+$10(A0),A0
    MOVE.L      -(A3),-(A0)
    MOVE.L      -(A3),-(A0)
    MOVE.L      -(A3),-(A0)
    MOVE.L      -(A3),-(A0)
    MOVE.W      #GRAF_GROWBOX,(A3)+
    JSR         aes_if
    JSR         testINTOUT0
  END;
END GrowBox;

PROCEDURE ShrinkBox(orgin,dest:Rectangle);

BEGIN
  ASSEMBLER
    MOVE.L      pubs,A0
    LEA         pubArrays.aINTIN+$8(A0),A0
    MOVE.L      -(A3),-(A0)
    MOVE.L      -(A3),-(A0)
    LEA         $10(A0),A0
    MOVE.L      -(A3),-(A0)
    MOVE.L      -(A3),-(A0)
    MOVE.W      #GRAF_SHRINKBOX,(A3)+
    JSR         aes_if
    JSR         testINTOUT0
  END;
END ShrinkBox;

PROCEDURE DragBox(start,bound:Rectangle; VAR loc:Point);

BEGIN
  ASSEMBLER
        MOVE.L  -(A3),-(A7)
              
        MOVE.L  pubs,A0
        LEA     pubArrays.aINTIN+16(A0),A0
        MOVE.L  -(A3),-(A0)
        MOVE.L  -(A3),-(A0)
        MOVE.L  -(A3),D0
        MOVE.L  -(A3),-(A0)
        MOVE.L  D0,-(A0)
        MOVE.W  #GRAF_DRAGBOX,(A3)+
        JSR     aes_if
        
        JSR     testINTOUT0
        MOVE.L  pubs,A0
        MOVE.L  (A7)+,A1
        MOVE.L  pubArrays.aINTOUT+2(A0),(A1)
  END;
END DragBox;
        
PROCEDURE RubberBox(start:Rectangle; VAR loc:Point);

BEGIN
  ASSEMBLER
      MOVE.L  -(A3),-(A7)
          
      MOVE.L  pubs,A0
      MOVE.L  -(A3),pubArrays.aINTIN+4(A0)
      MOVE.L  -(A3),pubArrays.aINTIN(A0)
      MOVE.W  #GRAF_RUBBOX,(A3)+
      JSR     aes_if
      
      JSR     testINTOUT0
      MOVE.L  pubs,A0
      MOVE.L  (A7)+,A1
      MOVE.L  pubArrays.aINTOUT+2(A0),(A1)
  END;
END RubberBox;
        
PROCEDURE SlideBox(tree:PtrObjTree;parent,child:CARDINAL;dir:SlideDirection;
                   VAR newPos:CARDINAL);

BEGIN
  ASSEMBLER
        MOVE.L  -(A3),-(A7)
        
        MOVE.L  pubs,A0
        MOVE.L  -(A3),pubArrays.aINTIN+2(A0)
        MOVE.W  -(A3),pubArrays.aINTIN(A0)
        MOVE.L  -(A3),pubArrays.ADDRIN(A0)
        MOVE.W  #GRAF_SLIDEBOX,(A3)+
        JSR     aes_if
        
        MOVE.L  pubs,A0
        MOVE.L  (A7)+,A1
        MOVE.W  pubArrays.aINTOUT(A0),(A1)
  END;
END SlideBox;
        
PROCEDURE WatchBox (    tree    : PtrObjTree;
                        index   : CARDINAL;
                        inState,
                        outState: OStateSet;
                    VAR inside  : BOOLEAN);
                  
  BEGIN
    ASSEMBLER
        MOVE.L  -(A3),-(A7)
        
        MOVE.L  pubs,A0
        MOVEQ   #0, D0
        SUBQ.L  #1, A3
        MOVE.B  -(A3), D0
        MOVE.W  D0, pubArrays.aINTIN+6(A0)
        SUBQ.L  #1, A3
        MOVE.B  -(A3), D0
        MOVE.W  D0, pubArrays.aINTIN+4(A0)
        MOVE.W  -(A3),pubArrays.aINTIN+2(A0)
        MOVE.W  #GRAF_WATCHBOX,(A3)+
        JSR     aes_if
        
        MOVE.L  pubs,A0
        MOVE.L  (A7)+,A1
        MOVE.W  pubArrays.aINTOUT(A0),(A1)
    END;
  END WatchBox;
  

END AESGraphics. 
(* $FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$00000407$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651$FFF8B651�$00000034T.......T.......T.......T.......T.......T.......T.......T.......T.......T.......$000009BF$00000AB8$00000B76$00000B9C$00000C26$00000D16$00000D3C$00000D60$00000DD7$00000F13$00000F5C$00000F82$00000FFA$00000034$000006DA$0000082F���*)
