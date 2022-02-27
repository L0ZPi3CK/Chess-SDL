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

What's currently done:
- Creating a board and assigning textures to all figures.
- All pieces movement that include:
1. Rook movement and beating    (Black and White)
2. Pawn movement and beating    (Black and White)
3. Knight movement and beating  (Black and White)
4. Bishop movement and beating  (Black and White)
5. Queen movement and beating   (Black and White)
6. King movement and beating    (Black and White)
- Putting away broken Pieces.
- Promotion of a pawn when it reaches the end line.
