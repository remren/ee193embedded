PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//412976/1366346/2.50/3/2/MOSFET P-Channel

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r80_40"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.4) (shapeHeight 0.8))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "SOT50P160X90-3N" (originalName "SOT50P160X90-3N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r80_40) (pt -0.8, 0.5) (rotation 90))
			(pad (padNum 2) (padStyleRef r80_40) (pt -0.8, -0.5) (rotation 90))
			(pad (padNum 3) (padStyleRef r80_40) (pt 0.8, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.45 1.075) (pt 1.45 1.075) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.45 1.075) (pt 1.45 -1.075) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.45 -1.075) (pt -1.45 -1.075) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.45 -1.075) (pt -1.45 1.075) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.4 0.8) (pt 0.4 0.8) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.4 0.8) (pt 0.4 -0.8) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.4 -0.8) (pt -0.4 -0.8) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.4 -0.8) (pt -0.4 0.8) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.4 0.3) (pt 0.1 0.8) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.05 0.8) (pt 0.05 0.8) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.05 0.8) (pt 0.05 -0.8) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.05 -0.8) (pt -0.05 -0.8) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.05 -0.8) (pt -0.05 0.8) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.2 0.95) (pt -0.4 0.95) (width 0.2))
		)
	)
	(symbolDef "NTA4151PT1G" (originalName "NTA4151PT1G")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 100 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 0 mils -45 mils) (rotation 0]) (justify "UpperLeft") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 300 mils 400 mils) (rotation 270) (pinLength 100 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 305 mils 400 mils) (rotation 90]) (justify "UpperLeft") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 300 mils -200 mils) (rotation 90) (pinLength 100 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 305 mils -200 mils) (rotation 90]) (justify "LowerLeft") (textStyleRef "Normal"))
		))
		(line (pt 300 mils 100 mils) (pt 300 mils -100 mils) (width 6 mils))
		(line (pt 300 mils 200 mils) (pt 300 mils 300 mils) (width 6 mils))
		(line (pt 100 mils 0 mils) (pt 200 mils 0 mils) (width 6 mils))
		(line (pt 200 mils 0 mils) (pt 200 mils 200 mils) (width 6 mils))
		(line (pt 300 mils 100 mils) (pt 230 mils 100 mils) (width 6 mils))
		(line (pt 300 mils 200 mils) (pt 230 mils 200 mils) (width 6 mils))
		(line (pt 230 mils 0 mils) (pt 300 mils 0 mils) (width 6 mils))
		(line (pt 230 mils 220 mils) (pt 230 mils 180 mils) (width 6 mils))
		(line (pt 230 mils -20 mils) (pt 230 mils 20 mils) (width 6 mils))
		(line (pt 230 mils 80 mils) (pt 230 mils 120 mils) (width 6 mils))
		(arc (pt 250 mils 100 mils) (radius 150 mils) (startAngle 0) (sweepAngle 360) (width 10  mils))
		(poly (pt 300 mils 100 mils) (pt 260 mils 120 mils) (pt 260 mils 80 mils) (pt 300 mils 100 mils) (width 10  mils))
		(attr "RefDes" "RefDes" (pt 450 mils 150 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 450 mils 50 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "NTA4151PT1G" (originalName "NTA4151PT1G") (compHeader (numPins 3) (numParts 1) (refDesPrefix Q)
		)
		(compPin "1" (pinName "G") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "S") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "D") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "NTA4151PT1G"))
		(attachedPattern (patternNum 1) (patternName "SOT50P160X90-3N")
			(numPads 3)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
			)
		)
		(attr "Mouser Part Number" "863-NTA4151PT1G")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/onsemi/NTA4151PT1G?qs=ZXBb0xZ9WeC9bannzQa%2FPw%3D%3D")
		(attr "Manufacturer_Name" "onsemi")
		(attr "Manufacturer_Part_Number" "NTA4151PT1G")
		(attr "Description" "ON Semiconductor NTA4151PT1G P-channel MOSFET Transistor, 0.76 A, -20 V, 3-Pin SC-75")
		(attr "<Hyperlink>" "http://www.onsemi.com/pub/Collateral/NTA4151P-D.PDF")
		(attr "<Component Height>" "0.9")
		(attr "<STEP Filename>" "NTA4151PT1G.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)