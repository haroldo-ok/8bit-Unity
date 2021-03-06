;
; Copyright (c) 2020 Anthony Beaucamp.
;
; This software is provided 'as-is', without any express or implied warranty.
; In no event will the authors be held liable for any damages arising from
; the use of this software.
;
; Permission is granted to anyone to use this software for any purpose,
; including commercial applications, and to alter it and redistribute it
; freely, subject to the following restrictions:
;
;   1. The origin of this software must not be misrepresented; you must not
;   claim that you wrote the original software. If you use this software in a
;   product, an acknowledgment in the product documentation would be
;   appreciated but is not required.
;
;   2. Altered source versions must be plainly marked as such, and must not
;   be misrepresented as being the original software.
;
;   3. This notice may not be removed or altered from any distribution.
;
;   4. The names of this software and/or it's copyright holders may not be
;   used to endorse or promote products derived from this software without
;   specific prior written permission.
;

	.export _DecodeTiles
	
	.import _tileCols, _tileRows
	.import _decodeWidth, _decodeHeight
	.import _blockWidth, _charmapWidth

; Zeropage addresses

.ifdef __APPLE2__
	tilesetDataZP = $ef
	charPointerZP = $ce
	row1PointerZP = $fb
	row2PointerZP = $fd
.endif

.ifdef __ATARI__
	tilesetDataZP = $e0
	charPointerZP = $e2
	row1PointerZP = $e4
	row2PointerZP = $e6
.endif	
	
.ifdef __CBM__
	tilesetDataZP = $61
	charPointerZP = $63
	row1PointerZP = $fb
	row2PointerZP = $fd
.endif	

.ifdef __LYNX__
	tilesetDataZP = $b3
	charPointerZP = $b5
	row1PointerZP = $b7
	row2PointerZP = $b9
.endif	

.ifdef __ATMOS__
	tilesetDataZP = $ef
	charPointerZP = $b5
	row1PointerZP = $b7
	row2PointerZP = $b9
.endif

	.segment	"BSS"

_tmpChr: .res 4
_curCol: .res 1
_curRow: .res 1

	.segment	"CODE"	

; ---------------------------------------------------------------
; void __near__ _DecodeTiles (void)
;	Convert Tilemap to Charmap
;	Zero Page Data:
;		tilesetDataZP: 16 bit address of tileset data
;		charPointerZP: 16 bit address of location on charmap (auto-updated)
;		row1PointerZP: 16 bit address of first screen line (auto-updated)
;		row2PointerZP: 16 bit address of second screen line (auto-updated)
; ---------------------------------------------------------------	

.proc _DecodeTiles: near

	ldx #0
loopRows: 
	cpx _tileRows
	bpl doneRows
	inx	

		ldy #0
	loopCols:
		cpy _tileCols
		bpl doneCols
		sty _curCol
		
			; Get Tile Value (x4)
			lda (charPointerZP),y
			asl A
			asl A
			
			; Get All Chars
			tay
			lda (tilesetDataZP),y
			sta _tmpChr+0
			iny
			lda (tilesetDataZP),y
			sta _tmpChr+1
			iny
			lda (tilesetDataZP),y
			sta _tmpChr+2
			iny
			lda (tilesetDataZP),y
			sta _tmpChr+3
			
			; Assign Chars to Buffer (4 bytes per Tile)
			lda _curCol
			asl A
			tay
			lda _tmpChr+0
			sta (row1PointerZP),y
			lda _tmpChr+2
			sta (row2PointerZP),y
			iny
			lda _tmpChr+1
			sta (row1PointerZP),y
			lda _tmpChr+3
			sta (row2PointerZP),y
				
		; Move to next col
		ldy _curCol
		iny		
		jmp loopCols	

	doneCols:		
		
		; Update location in charmap
		clc	
		lda charPointerZP			
		adc _charmapWidth
		sta charPointerZP	
		bcc nocarryChrPtr	; Check if carry to high byte
		inc charPointerZP+1
	nocarryChrPtr:

		; Update location in screen buffer (line 1)
		clc	
		lda row1PointerZP			
		adc _blockWidth
		sta row1PointerZP	
		bcc nocarryScrPtr1	; Check if carry to high byte
		inc row1PointerZP+1
	nocarryScrPtr1:

		; Update location in screen buffer (line 2)
		clc	
		lda row2PointerZP		
		adc _blockWidth
		sta row2PointerZP
		bcc nocarryScrPtr2	; Check if carry to high byte
		inc row2PointerZP+1
	nocarryScrPtr2:
	
	; Move to next row
	jmp loopRows

doneRows:
	rts

.endproc	
