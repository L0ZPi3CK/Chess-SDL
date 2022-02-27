# Chess-SDL
 
First, after downloading the folder you have to make sure that path to SDL2 is correct
Open .sln file, go to properties an check:
1. VC++ Directories:  
![screen1s](https://user-images.githubusercontent.com/84734341/155896312-d55fda5b-2734-45ca-bb51-1dc2fd4b61ed.png)
2. C/C++/General:  
![screen2s](https://user-images.githubusercontent.com/84734341/155896317-6bda2796-3882-4202-b22a-684d739f1af7.png)
3. Linker/General:  
![screen3s](https://user-images.githubusercontent.com/84734341/155896328-5297074e-e2cc-454b-89a5-4198880c5f00.png)
4. Linker/Input:  
![screen4s](https://user-images.githubusercontent.com/84734341/155896331-bdf7e37f-575e-433d-9d7f-ee6f020d37ed.png)  
  
***Or you can try to save folder as D:\Chess-SDL  

!!! I created this chess without any chess engine.  
!!! The game consists of alternately moving the pawns until the king is killed (king mate)

What's currently done:
1. Creating a board and assigning textures to all figures.
2. All pieces movement that include:
- Rook movement and beating    (Black and White)
- Pawn movement and beating    (Black and White)
- Knight movement and beating  (Black and White)
- Bishop movement and beating  (Black and White)
- Queen movement and beating   (Black and White)
- King movement and beating    (Black and White)
4. Putting away broken Pieces.
5. Promotion of a pawn when it reaches the end line.
6. Alternating movement of pieces  

What's to do:
1. Matting a king
