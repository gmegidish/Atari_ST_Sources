
		;x,y,z,-

	ifne	0

.s:		set	220
.y:		set	-5

	rept	12
		dc.w	-7*.s,.y*.s,0*.s,0
		dc.w	-6*.s,.y*.s,0*.s,0
		dc.w	-5*.s,.y*.s,0*.s,0
		dc.w	-4*.s,.y*.s,0*.s,0
		dc.w	-3*.s,.y*.s,0*.s,0
		dc.w	-2*.s,.y*.s,0*.s,0
		dc.w	-1*.s,.y*.s,0*.s,0
		dc.w	0*.s,.y*.s,0*.s,0
		dc.w	1*.s,.y*.s,0*.s,0
		dc.w	2*.s,.y*.s,0*.s,0
		dc.w	3*.s,.y*.s,0*.s,0
		dc.w	4*.s,.y*.s,0*.s,0
		dc.w	5*.s,.y*.s,0*.s,0
		dc.w	6*.s,.y*.s,0*.s,0
		dc.w	7*.s,.y*.s,0*.s,0
.y:		set	.y+1
	endr


	endc


.s:		set	22

		dc.w	-70*.s,-50*.s,-20*.s,0
		dc.w	-60*.s,-50*.s,-20*.s,0
		dc.w	-50*.s,-50*.s,-20*.s,0
		dc.w	-40*.s,-50*.s,-20*.s,0
		dc.w	-30*.s,-50*.s,-20*.s,0
		dc.w	-20*.s,-50*.s,-20*.s,0
		dc.w	-10*.s,-50*.s,-20*.s,0
		dc.w	-0*.s,-50*.s,-20*.s,0
		dc.w	10*.s,-50*.s,-20*.s,0
		dc.w	20*.s,-50*.s,-20*.s,0
		dc.w	30*.s,-50*.s,-20*.s,0
		dc.w	40*.s,-50*.s,-20*.s,0
		dc.w	50*.s,-50*.s,-20*.s,0
		dc.w	60*.s,-50*.s,-20*.s,0
		dc.w	70*.s,-50*.s,-20*.s,0

		dc.w	-70*.s,40*.s,-20*.s,0
		dc.w	-60*.s,40*.s,-20*.s,0
		dc.w	-50*.s,40*.s,-20*.s,0
		dc.w	-40*.s,40*.s,-20*.s,0
		dc.w	-30*.s,40*.s,-20*.s,0
		dc.w	-20*.s,40*.s,-20*.s,0
		dc.w	-10*.s,40*.s,-20*.s,0
		dc.w	-0*.s,40*.s,-20*.s,0
		dc.w	10*.s,40*.s,-20*.s,0
		dc.w	20*.s,40*.s,-20*.s,0
		dc.w	30*.s,40*.s,-20*.s,0
		dc.w	40*.s,40*.s,-20*.s,0
		dc.w	50*.s,40*.s,-20*.s,0
		dc.w	60*.s,40*.s,-20*.s,0
		dc.w	70*.s,40*.s,-20*.s,0

		dc.w	-70*.s,-50*.s,-20*.s,0
		dc.w	-70*.s,-40*.s,-20*.s,0
		dc.w	-70*.s,-30*.s,-20*.s,0
		dc.w	-70*.s,-20*.s,-20*.s,0
		dc.w	-70*.s,-10*.s,-20*.s,0
		dc.w	-70*.s,0*.s,-20*.s,0
		dc.w	-70*.s,10*.s,-20*.s,0
		dc.w	-70*.s,20*.s,-20*.s,0
		dc.w	-70*.s,30*.s,-20*.s,0
		dc.w	-70*.s,40*.s,-20*.s,0

		dc.w	70*.s,-50*.s,-20*.s,0
		dc.w	70*.s,-40*.s,-20*.s,0
		dc.w	70*.s,-30*.s,-20*.s,0
		dc.w	70*.s,-20*.s,-20*.s,0
		dc.w	70*.s,-10*.s,-20*.s,0
		dc.w	70*.s,0*.s,-20*.s,0
		dc.w	70*.s,10*.s,-20*.s,0
		dc.w	70*.s,20*.s,-20*.s,0
		dc.w	70*.s,30*.s,-20*.s,0
		dc.w	70*.s,40*.s,-20*.s,0

;l2

		dc.w	-70*.s,-50*.s,-10*.s,0
		dc.w	-60*.s,-50*.s,-10*.s,0
		dc.w	-50*.s,-50*.s,-10*.s,0
		dc.w	-40*.s,-50*.s,-10*.s,0
		dc.w	-30*.s,-50*.s,-10*.s,0
		dc.w	-20*.s,-50*.s,-10*.s,0
		dc.w	-10*.s,-50*.s,-10*.s,0
		dc.w	-0*.s,-50*.s,-10*.s,0
		dc.w	10*.s,-50*.s,-10*.s,0
		dc.w	20*.s,-50*.s,-10*.s,0
		dc.w	30*.s,-50*.s,-10*.s,0
		dc.w	40*.s,-50*.s,-10*.s,0
		dc.w	50*.s,-50*.s,-10*.s,0
		dc.w	60*.s,-50*.s,-10*.s,0
		dc.w	70*.s,-50*.s,-10*.s,0

		dc.w	-70*.s,40*.s,-10*.s,0
		dc.w	-60*.s,40*.s,-10*.s,0
		dc.w	-50*.s,40*.s,-10*.s,0
		dc.w	-40*.s,40*.s,-10*.s,0
		dc.w	-30*.s,40*.s,-10*.s,0
		dc.w	-20*.s,40*.s,-10*.s,0
		dc.w	-10*.s,40*.s,-10*.s,0
		dc.w	-0*.s,40*.s,-10*.s,0
		dc.w	10*.s,40*.s,-10*.s,0
		dc.w	20*.s,40*.s,-10*.s,0
		dc.w	30*.s,40*.s,-10*.s,0
		dc.w	40*.s,40*.s,-10*.s,0
		dc.w	50*.s,40*.s,-10*.s,0
		dc.w	60*.s,40*.s,-10*.s,0
		dc.w	70*.s,40*.s,-10*.s,0

		dc.w	-70*.s,-50*.s,-10*.s,0
		dc.w	-70*.s,-40*.s,-10*.s,0
		dc.w	-70*.s,-30*.s,-10*.s,0
		dc.w	-70*.s,-20*.s,-10*.s,0
		dc.w	-70*.s,-10*.s,-10*.s,0
		dc.w	-70*.s,0*.s,-10*.s,0
		dc.w	-70*.s,10*.s,-10*.s,0
		dc.w	-70*.s,20*.s,-10*.s,0
		dc.w	-70*.s,30*.s,-10*.s,0
		dc.w	-70*.s,40*.s,-10*.s,0

		dc.w	70*.s,-50*.s,-10*.s,0
		dc.w	70*.s,-40*.s,-10*.s,0
		dc.w	70*.s,-30*.s,-10*.s,0
		dc.w	70*.s,-20*.s,-10*.s,0
		dc.w	70*.s,-10*.s,-10*.s,0
		dc.w	70*.s,0*.s,-10*.s,0
		dc.w	70*.s,10*.s,-10*.s,0
		dc.w	70*.s,20*.s,-10*.s,0
		dc.w	70*.s,30*.s,-10*.s,0
		dc.w	70*.s,40*.s,-10*.s,0

;l3
		dc.w	-70*.s,-50*.s,0*.s,0
		dc.w	-60*.s,-50*.s,0*.s,0
		dc.w	-50*.s,-50*.s,0*.s,0
		dc.w	-40*.s,-50*.s,0*.s,0
		dc.w	-30*.s,-50*.s,0*.s,0
		dc.w	-20*.s,-50*.s,0*.s,0
		dc.w	-10*.s,-50*.s,0*.s,0
		dc.w	-0*.s,-50*.s,0*.s,0
		dc.w	10*.s,-50*.s,0*.s,0
		dc.w	20*.s,-50*.s,0*.s,0
		dc.w	30*.s,-50*.s,0*.s,0
		dc.w	40*.s,-50*.s,0*.s,0
		dc.w	50*.s,-50*.s,0*.s,0
		dc.w	60*.s,-50*.s,0*.s,0
		dc.w	70*.s,-50*.s,0*.s,0

		dc.w	-70*.s,40*.s,0*.s,0
		dc.w	-60*.s,40*.s,0*.s,0
		dc.w	-50*.s,40*.s,0*.s,0
		dc.w	-40*.s,40*.s,0*.s,0
		dc.w	-30*.s,40*.s,0*.s,0
		dc.w	-20*.s,40*.s,0*.s,0
		dc.w	-10*.s,40*.s,0*.s,0
		dc.w	-0*.s,40*.s,0*.s,0
		dc.w	10*.s,40*.s,0*.s,0
		dc.w	20*.s,40*.s,0*.s,0
		dc.w	30*.s,40*.s,0*.s,0
		dc.w	40*.s,40*.s,0*.s,0
		dc.w	50*.s,40*.s,0*.s,0
		dc.w	60*.s,40*.s,0*.s,0
		dc.w	70*.s,40*.s,0*.s,0

		dc.w	-70*.s,-50*.s,0*.s,0
		dc.w	-70*.s,-40*.s,0*.s,0
		dc.w	-70*.s,-30*.s,0*.s,0
		dc.w	-70*.s,-20*.s,0*.s,0
		dc.w	-70*.s,-10*.s,0*.s,0
		dc.w	-70*.s,0*.s,0*.s,0
		dc.w	-70*.s,10*.s,0*.s,0
		dc.w	-70*.s,20*.s,0*.s,0
		dc.w	-70*.s,30*.s,0*.s,0
		dc.w	-70*.s,40*.s,0*.s,0

		dc.w	70*.s,-50*.s,0*.s,0
		dc.w	70*.s,-40*.s,0*.s,0
		dc.w	70*.s,-30*.s,0*.s,0
		dc.w	70*.s,-20*.s,0*.s,0
		dc.w	70*.s,-10*.s,0*.s,0
		dc.w	70*.s,0*.s,0*.s,0
		dc.w	70*.s,10*.s,0*.s,0
		dc.w	70*.s,20*.s,0*.s,0
		dc.w	70*.s,30*.s,0*.s,0
		dc.w	70*.s,40*.s,0*.s,0


;�vriga 30
		dc.w	-40*.s,0*.s,35*.s,0
		dc.w	-30*.s,0*.s,35*.s,0
		dc.w	-20*.s,0*.s,35*.s,0
		dc.w	-10*.s,0*.s,35*.s,0
		dc.w	-0*.s,0*.s,35*.s,0
		dc.w	10*.s,0*.s,35*.s,0
		dc.w	20*.s,0*.s,35*.s,0
		dc.w	30*.s,0*.s,35*.s,0
		dc.w	40*.s,0*.s,35*.s,0

		dc.w	-40*.s,0*.s,-35*.s,0
		dc.w	-30*.s,0*.s,-35*.s,0
		dc.w	-20*.s,0*.s,-35*.s,0
		dc.w	-10*.s,0*.s,-35*.s,0
		dc.w	-0*.s,0*.s,-35*.s,0
		dc.w	10*.s,0*.s,-35*.s,0
		dc.w	20*.s,0*.s,-35*.s,0
		dc.w	30*.s,0*.s,-35*.s,0
		dc.w	40*.s,0*.s,-35*.s,0

		dc.w	-40*.s,0*.s,-25*.s,0
		dc.w	-40*.s,0*.s,-15*.s,0
		dc.w	-40*.s,0*.s,-5*.s,0
		dc.w	-40*.s,0*.s,5*.s,0
		dc.w	-40*.s,0*.s,15*.s,0
		dc.w	-40*.s,0*.s,25*.s,0

		dc.w	40*.s,0*.s,-25*.s,0
		dc.w	40*.s,0*.s,-15*.s,0
		dc.w	40*.s,0*.s,-5*.s,0
		dc.w	40*.s,0*.s,5*.s,0
		dc.w	40*.s,0*.s,15*.s,0
		dc.w	40*.s,0*.s,25*.s,0