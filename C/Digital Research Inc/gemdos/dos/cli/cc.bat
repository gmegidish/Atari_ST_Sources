
CHECK %1
CP68 %1.C %1.I
C068 %1.I %1.1 %1.2 %1.3 -F
DEL %1.I
C168 %1.1 %1.2 %1.S
DEL %1.1
DEL %1.2
AS68 -L -U -S c:\alyc\ %1.S
DEL %1.S
