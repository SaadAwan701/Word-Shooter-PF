//============================================================================
// Name        : cookie-crush.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Cookie  Crush...
//============================================================================
#ifndef WORD_SHOOTER_CPP
#define WORD_SHOOTER_CPP

//#include <GL/gl.h>
//#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include "util.h"
using namespace std;
#define MAX(A,B) ((A) > (B) ? (A):(B)) // defining single line functions....
#define MIN(A,B) ((A) < (B) ? (A):(B))
#define ABS(A) ((A) < (0) ? -(A):(A))
#define FPS 30

string * dictionary;
int dictionarysize = 369646;
#define KEY_ESC 27 // A
int universal=0;
int a1[5]={20,0,19,19,11};

// 20,30,30
const int bradius = 30; // ball radius in pixels...
float timemark = 0.00f;  // Time in seconds
     // Flag to indicate game over state
const float maxTime = 120.0f; 

int width = 930, height = 660;
int byoffset = bradius;

int nxcells = (width - bradius) / (2 * bradius);
int nycells = (height - byoffset /*- bradius*/) / (2 * bradius);
int nfrows = 2; // initially number of full rows //
float score = 0;
int **board; // 2D-arrays for holding the data...
int bwidth = 130;
int bheight = 10;
int bsx,bsy;
//Can you make a timer of 120 seconds and display it on the screen

int startingTime = 0; // Elapsed time in seconds
bool gameOver = false; // Game over flag
const int Calphabets = 26;
float xspeed = 0;  // X speed of the ball
float yspeed = 0;
int B1 =  width / 2;  // Initial ball clposition (centered)
int B2 = 0;          // Ball is at the bottom initially
float BSpeed = 26.0f;
bool ballshooter = false;  // Ball is not launched yet 
enum Calphaets {
	AL_A, AL_B, AL_C, AL_D, AL_E, AL_F, AL_G, AL_H, AL_I, AL_J, AL_K, AL_L, AL_M, AL_N, AL_O, AL_P, AL_Q, AL_R, AL_S, AL_T, AL_U, AL_W, AL_X, AL_y, AL_Z
};
const int totalTime = 120; 
GLuint texture[Calphabets];
GLuint tid[Calphabets];
string tnames[] = { "a.bmp", "b.bmp", "c.bmp", "d.bmp", "e.bmp", "f.bmp", "g.bmp", "h.bmp", "i.bmp", "j.bmp",
"k.bmp", "l.bmp", "m.bmp", "n.bmp", "o.bmp", "p.bmp", "q.bmp", "r.bmp", "s.bmp", "t.bmp", "u.bmp", "v.bmp", "w.bmp",
"x.bmp", "y.bmp", "z.bmp" };
GLuint mtid[Calphabets];
int awidth = 60, aheight = 60; // 60x60 pixels cookies...
int Calpha[5][15];  // Store random pairs of Calphaets for 15 positions
int ball;

// Function to check if a word exists in the dictionary using linear search
// Returns true if the word is found, otherwise false
bool wordExists(const string dict[], int size, const string& word) {
    for(int i = 0; i < size; ++i){
        if(dict[i] == word){
            return true; // Word found
        }
    }
    return false; // Word not found
}


// Function to search for words in the grid and remove them if found
void searchAndRemoveWords(const string dict[], int dictionarysize, int Calpha[][2]) {
    // Define minimum and maximum word lengths
    const int MiniumumWordLength = 3;
    const int MaxiumumWordLength = 17;

    // Iterate through each cell in the grid
    for(int row = 0; row < 3; ++row) {
        for(int col = 0; col < 17; ++col) {
            // Skip if the current cell is empty
            if(Calpha[col][row] == -1)
                continue;

           
   if(col + MiniumumWordLength <= 17) { // Ensure enough space
                string WR = "";
                for(int k = col; k < 17 && (k - col) < MaxiumumWordLength; ++k) {
                    if(Calpha[k][row] == -1)
                        break;
                    WR += ('a' + Calpha[k][row]); // Convert index to character
                    if(WR  .length() >= MiniumumWordLength) {
                        if (wordExists(dict, dictionarysize, WR)) {
                            // Word found: Remove the word from grid
                            for(int m = col;m < col+ WR . length() && m <17; ++m) {
                                Calpha[m][row] = -1;
                            }
                          //  score += WR.length() * 10; // Example scoring
                            cout << "popped word: " << WR << endl;
      }
     }
   }
   }

            // 2. Right to Left (Horizontal)
            if(col - MiniumumWordLength +1 >=0) { // Ensure enough space
                string wordRL = "";
                for(int k = col; k >=0 && (col -k) < MaxiumumWordLength; --k) {
                    if(Calpha[k][row] == -1)
                        break;
                    wordRL += ('a' + Calpha[k][row]); // Convert index to character
                    if(wordRL.length() >= MiniumumWordLength) {
                        if(wordExists(dict, dictionarysize, wordRL)) {
                            // Word found: Remove the word from grid
                            for(int m = col; m >= col - wordRL.length() +1 && m >=0; --m) {
                                Calpha[m][row] = -1;
                            }
                           // score += wordRL.length() * 10;
                            cout << "Word found and removed: " << wordRL << endl;
                        }
                    }
                }
            }

            // 3. Top to Bottom (Vertical)
            if(row + MiniumumWordLength <=3) { // Only 2 rows
                string WK = "";
                for(int k = row; k < 3 && (k - row) < MaxiumumWordLength; ++k) {
                    if(Calpha[col][k] == -1)
                        break;
                    WK += ('a' + Calpha[col][k]); // Convert index to character
                    if(WK.length() >= MiniumumWordLength) {
                        if(wordExists(dict, dictionarysize, WK)) {
                            // Word found: Remove the word from grid
                            for(int m = row; m < row + WK.length() && m <3; ++m) {
                                Calpha[col][m] = -1;
                            }
                          //  score += WK.length() * 10;
                            cout << "Word found and removed: " << WK << endl;
                        }
                    }
                }
            }

            // 4. Bottom to Top (Vertical)
            if(row - MiniumumWordLength +1 >=0) { // Only 2 rows
                string WBT = "";
                for(int k = row; k >=0 && (row -k) < MaxiumumWordLength; --k) {
                    if(Calpha[col][k] == -1)
                        break;
                    WBT += ('a' + Calpha[col][k]); // Convert index to character
                    if(WBT.length() >= MiniumumWordLength) {
                        if(wordExists(dict, dictionarysize, WBT)) {
                            // Word found: Remove the word from grid
                            for(int m = row; m >= row - WBT.length() +1 && m >=0; --m) {
                                Calpha[col][m] = -1;
                            }
                        //    score += WBT.length() * 10;
                            cout << "Word found and removed: " << WBT << endl;
                        }
                    }
                }
            }
        }
    }
}

bool findAlreadyMatchedWords(int grid[2][15], const string dictionary[], int dictionarySize) {
    vector<string> foundWords; // Vector to store found words

    // Define all 8 possible directions: 
    // (deltacolumn, drow)
    // 1. Right, 2. Left, 3. Down, 4. Up,
    // 5. Down-Right, 6. Down-Left, 7. Up-Right, 8. Up-Left
const int directions[8][2] = {
  {1,0},    // Right
  {-1,0},   // Left
  {0,1},    // Down
  {0,-1},   // Up
  {1,1},    // Down-Right
 {-1,1},   // Down-Left
  {1,-1},   // Up-Right
  {-1,-1}   // Up-Left
    };
// Iterate through each word in the dictionary
    for(int w = 0; w < dictionarySize; ++w) {
        string word = dictionary[w];
        int wordLegth= word.length();
 // Skip words that are longer than the grid allows in any direction
        if(wordLegth < 3 || wordLegth> 15) {
            continue;
        }

        // Iterate through each cell in the grid as a potential starting point
        for(int col = 0; col < 5; ++col) {
            for(int row = 0; row < 15; ++row) {
                // Iterate through all 8 directions from the current cell
                for(int d = 0; d < 8; ++d) {
                    int deltacolumn = directions[d][0];
                    int drow = directions[d][1];

                    // Calculate the ending position of the word
                    int endcolumn = col + (wordLegth - 1) * deltacolumn;
                    int endrow = row + (wordLegth - 1) * drow;

                    // Check if the word fits within the grid boundaries
                    if(endcolumn < 0 || endcolumn >= 5 || endrow < 0 || endrow >= 15) {
                        continue; // Word does not fit in this direction
                    }

                    bool match = true; // Flag to check if the word matches

                    // Check each character in the word
                    for(int k = 0; k < wordLegth; ++k) {
                        int current_col = col + k * deltacolumn;
                        int current_row = row + k * drow;

                        int grid_val = grid[current_col][current_row];
                        char grid_char = 'a' + grid_val; // Convert grid value to character

                        // Compare the grid character with the word's character
                        if(grid_char != word[k]) {
                            match = false;
                            break; // Mismatch found, no need to check further
                        }
                    }

                    // If a match is found, add the word to the foundWords vector
                    if(match) {
                        foundWords.push_back(word);
                        cout<<word<<endl;
                        for (int m = 0; m < wordLegth; m++){
                            int current_col = col + m * deltacolumn;
                            int current_row = row + m * drow;
                            grid[current_col][current_row] = rand()%26; // Mark as used
                        }
                        return true;
                        break;
                    }
                }
            }
        }
    }
    return false; // Return all found words
}


void findWordsInGrid( int grid[2][15], const string dictionary[], int dictionarySize) {
    string largestWord = ""; // To store the largest word found
    int start_col = -1, start_row = -1; // Starting indices of the largest word
    int endcolumn = -1, endrow = -1;     // Ending indices of the largest word
    int final_deltacolumn = 0, final_drow = 0; 
    // Define all 8 possible directions: 
    // (deltacolumn, drow)
    // 1. Right, 2. Left, 3. Down, 4. Up,
    // 5. Down-Right, 6. Down-Left, 7. Up-Right, 8. Up-Left
    const int directions[8][2] = {
        {1, 0},    // Right
        {-1, 0},   // Left
        {0, 1},    // Down
        {0, -1},   // Up
        {1, 1},    // Down-Right
        {-1, 1},   // Down-Left
        {1, -1},   // Up-Right
        {-1, -1}   // Up-Left
    };

    // Iterate through each word in the dictionary
    for(int w = 0; w < dictionarySize; ++w) {
        string word = dictionary[w];
        int wordLegth = word.length();

        // Skip words that are longer than the grid allows in any direction
        if(wordLegth < 3 || wordLegth > 15) {
            continue;
        }

        // Iterate through each cell in the grid as a potential starting point
        for(int col=0; col<5; ++col) {
    for(int row =0; row <15; ++row) {
                // Iterate through all 8 directions from the current cell
                for(int d = 0; d < 8; ++d) {
                    int deltacolumn = directions[d][0];
               int drow = directions[d][1];

                    // Calculate the ending position of the word
                    int endcolumn = col +(wordLegth- 1) * deltacolumn;
                    int endrow = row +(wordLegth - 1) * drow;

                    // Check if the word fits within the grid boundaries
                    if(endcolumn < 0 || endcolumn >= 5 || endrow < 0 || endrow >= 15) {
                        continue; // Word does not fit in this direction
                    }

                    bool match = true; // Flag to check if the word matches

                    // Check each character in the word
                    for(int k = 0; k < wordLegth; ++k) {
                        int current_col = col + k * deltacolumn;
                        int current_row = row + k * drow;

                        int grid_val = grid[current_col][current_row];
                        char grid_char = 'a' + grid_val; // Convert grid value to character

                        // Compare the grid character with the word's character
                        if(grid_char != word[k]) {
                            match = false;
                            break; // Mismatch found, no need to check further
                        }
                    }

                    // If a match is found, add the word to the foundWords vector
                    if(match) {
                    	if (wordLegth > largestWord.length()) {
                            largestWord = word;

                            
        start_col = col;
        start_row = row;
         endcolumn = endcolumn;
       endrow = endrow;
        final_deltacolumn = deltacolumn;
       final_drow = drow;
    }
    }
    }
   }
        }
    }

	if (!largestWord.empty()) {
		int wordLegth = largestWord.length();
		for (int m = 0; m < wordLegth; ++m) {
		    int current_col = start_col+ m * final_deltacolumn;
		    int current_row = start_row+ m * final_drow;
		    grid[current_col][current_row] = -1; // Mark as used
		}
    	}	
    cout<<largestWord<<endl;
		score+=largestWord.length()*10;
	// Return all found words
}

void GAB() {
	do{
		for(int j=0;j<5;j++){
		    if(j<2)
			    for (int i = 0; i < 15; ++i) {
				Calpha[j][i] = rand() % 26;  // Random Calphaet index for first row
			    }
		    else
		       	    for(int i=0;i<15;i++)
		       	    	Calpha[j][i]=-1;
		}
    }while(findAlreadyMatchedWords(Calpha,dictionary,dictionarysize));
    ball=rand()%26;
}
//USED THIS CODE FOR WRITING THE IMAGES TO .bin FILE
void RegisterTextures_Write()
//Function is used to load the textures from the
// files and display
{
	// allocate a texture name
	glGenTextures(Calphabets, tid);
	vector<unsigned char> data;
	ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each cookies data...

	for (int i = 0; i <Calphabets; ++i) {

		// Read current cookie

   ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			ofile.write((char*)&length, sizeof(int));
		}
		ofile.write((char*)&data[0], sizeof(char) * data.size());

		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
			wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, awidth, aheight, GL_RGB,
			GL_UNSIGNED_BYTE, &data[0]);
	}
	ofile.close();

}
			void RegisterTextures()
			/*Function is used to load the textures from the
			* files and display*/
			{
				// allocate a texture name
				glGenTextures(Calphabets, tid);

				vector<unsigned char> data;
				ifstream ifile("image-data.bin", ios::binary | ios::in);

				if (!ifile) {
					cout << " Couldn't Read the Image Data file ";
					//exit(-1);
				}
				// now load each cookies data...
				int length;
				ifile.read((char*)&length, sizeof(int));
				data.resize(length, 0);
				for (int i = 0; i < Calphabets; ++i) {
					// Read current cookie
					//ReadImage(tnames[i], data);
					/*if (i == 0) {
					int length = data.size();
					ofile.write((char*) &length, sizeof(int));
					}*/
					ifile.read((char*)&data[0], sizeof(char)* length);

					mtid[i] = tid[i];
					// select our current texture
glBindTexture(GL_TEXTURE_2D, tid[i]);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
GL_LINEAR_MIPMAP_NEAREST);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

bool wrap = true;
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
wrap ? GL_REPEAT : GL_CLAMP);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
wrap ? GL_REPEAT : GL_CLAMP);

      
				  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, awidth, aheight, GL_RGB,
						GL_UNSIGNED_BYTE, &data[0]);
				}
				ifile.close();
			}
void DrawCalphaet(const Calphaets &cname, int sx, int sy, int cwidth = 60,
	int cheight = 60)
	/*Draws a specfic cookie at given position coordinate
	* sx = position of x-axis from left-bottom
	* sy = position of y-axis from left-bottom
	* cwidth= width of displayed cookie in pixels
	* cheight= height of displayed cookiei pixels.
	* */
{
	float fwidth = (float)cwidth / width * 2, fheight = (float)cheight
		/ height * 2;
	float fx = (float)sx / width * 2 - 1, fy = (float)sy / height * 2 - 1;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();
	

	glColor4f(1, 1, 1, 1);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}

void DrawShooter(const Calphaets &cname, int sx, int sy, int cwidth = 60,
	int cheight = 60)
	/*Draws a specfic cookie at given position coordinate
	* sx = position of x-axis from left-bottom
	* sy = position of y-axis from left-bottom
	* cwidth= width of displayed cookie in pixels
	* cheight= height of displayed cookiei pixels.
	* */
{
	float fwidth = (float)cwidth / width * 2, fheight = (float)cheight
		/ height * 2;
	float fx = (float)sx / width * 2 - 1, fy = (float)sy / height * 2 - 1;
	fx=fx-1;
	fy=fy-1;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
int GetCalphaet() {
	return GetRandInRange(1, 26);
}

void Pixels2Cell(int px, int py, int & cx, int &cy) {
}
void Cell2Pixels(int cx, int cy, int & px, int &py)
// converts the cell coordinates to pixel coordinates...
{
}
void DrawShooter(int sx, int sy, int cwidth = 60, int cheight = 60)

{
	float fwidth = (float)cwidth / width * 2, fheight = (float)cheight
		/ height * 2;
	float fx = (float)sx / width * 2 - 1, fy = (float)sy / height * 2 - 1;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, -1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();
	

	glColor4f(1, 1, 1, 1);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
/*
* Main Canvas drawing function.
* */
bool CheckBallCollisionWithCalphaets(int B1, int B2, int radius, int rowY, int Calpha[5][15],int r) {
	    for (int i = 0; i < 15; ++i) {
		int CalphaetXU = i * 60-40;  // x position of the Calphaet (you may need to adjust based on your layout)
		int CalphaetYU = rowY;  // y position of the Calphaet (upper row)

		 if(Calpha[r][i] == -1)
				continue;  // Skip empty cells
		// Check if the ball's bounding box overlaps with the Calphaet's bounding box
		//cout<<B1<<' '<<B2<<CalphaetXU<<CalphaetYU<<endl;
		if (B1 + radius > CalphaetXU && B1 - radius < CalphaetXU + 60 && 
		    B2 + radius > CalphaetYU && B2 - radius < CalphaetYU + 60) {
				cout<<r<<i<<endl;
				//Calpha[r][i]=ball;	
		    return true;  
		}
	    }
    return false;  // No collision
}

void addToGrid(int Calpha[5][15],int bx,int by){
	int x=(bx)/60;
	int y=(height-by-60)/60;
	Calpha[y][x]=ball;
	cout<<height<<' '<<y<<' '<<x<<' '<<by<<' '<<bx<<endl;
}

void DisplayFunction() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background to white
    glClear(GL_COLOR_BUFFER_BIT);
	if (gameOver) {
        // If game is over, show the "Game Over" screen
        glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
        DrawString(width / 2 - 80, height / 2, width, height, "GAME OVER", colors[BROWN]);
        DrawString(width / 2 - 90, height / 2 - 30, width, height, "Game over, run the code again", colors[BLUE]);
    }else{
		// Update ball position based on the calculated direction and speed
		B1 += xspeed * BSpeed;
		B2 += yspeed * BSpeed;

		
		if (B1 < bradius - 50) {
			B1 = bradius;  // Prevent ball from going out of bounds
			xspeed = -xspeed;  // Reflect the ball horizontally
		}
		if (B1 > width - bradius) {
			B1 = width - bradius;  
			xspeed = -xspeed;  
		}

		 
if (B2 < bradius) {
			B2 = bradius;  // Prevent ball from going out of bounds
			yspeed = -yspeed;  // Reflect the ball vertically
		}
if (B2 > height - bradius) {
			B2 = height - bradius;  // Prevent ball from going out of bounds
			yspeed = -yspeed;  // Reflect the ball vertically
		}

		// Check for collision with upper row _Pof Calphaets
		for(int i=0;i<5;i++){
			if (CheckBallCollisionWithCalphaets(B1, B2, bradius, height - (i*60+140), Calpha,i)) {
				// Handle collision (e.g., destroy ball and spawn a new one)
				addToGrid(Calpha,B1,B2);
				findWordsInGrid(Calpha,dictionary,dictionarysize);
	B1 = width / 2;  // Reset ball position
	B2 = 0;
	xspeed = 0; 
yspeed = 0;
	ballshooter = false;  // Ball is not launched
	ball =a1[universal%5];  // Get new Calphaet ball
		universal++;
			}
		}
		// Draw the ball (Calphaet) at the updated position

		// Draw the upper row of Calphaets
			
		int deviation=120;
		for(int j=0;j<5;j++){
			int xy = 10;
			for (int i = 0; i < 15; i++) {
			int curr_height=height-deviation;
			//DrawCalphaet((Calphaets)Calpha[i][0], xy, height - 120, awidth, aheight); // First row
			DrawCalphaet((Calphaets)Calpha[j][i], xy, height - deviation, awidth, aheight); // Second row
			xy = xy + 60;
			}
			 deviation+=60;
		}
		DrawCalphaet((Calphaets)ball, B1, B2, awidth, aheight);	

		// Draw other game elements (score, timer, etc.)
		DrawString(40, height - 20, width, height + 5, "Score " + Num2Str(score), colors[BLUE_VIOLET]);
		DrawString(width / 2 - 30, height - 25, width, height, "Time Left:" + Num2Str(totalTime-startingTime) + " secs", colors[RED]);
DrawString(width /2 + 200 , height - 25, width , height , " Saad", colors [RED]);
		DrawShooter((width / 2) - 35, 0, bwidth, bheight);
	}
    glutSwapBuffers();
}



/* Function sets canvas size (drawing area) in pixels...
*  that is what dimensions (x and y) your game will have
*  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
* */
void SetCanvasSize(int width, int height) {
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.*/
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
* is pressed from the keyboard
*
* You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
*
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
*
* */

void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	}
	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	* this function*/
	/*
	glutPostRedisplay();
	*/
}
/*This function is called (automatically) whenever your mouse moves witin inside the game window
*
* You will have to add the necessary code here for finding the direction of shooting
*
* This function has two arguments: x & y that tells the coordinate of current position of move mouse
*
* */

void MouseMoved(int x, int y) {
	//If mouse pressed then check than swap the balls and if after swaping balls dont brust then reswap the balls

}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
*
* You will have to add the necessary code here for shooting, etc.
*
* This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
* x & y that tells the coordinate of current position of move mouse
*
* */
 // Speed of the ball movement
 // Function to check if the ball collides with any Calphaet in the given row

void MouseClicked(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

if (ballshooter) return;
BSpeed = 25.0f;
        float mouseX = (float)x / width * 2 - 1;
        float mouseY = -((float)y / height * 2 - 1);

      
        float dx = mouseX - (float)B1 / width * 2 + 1;
        float dy = mouseY - (float)B2 / height * 2 + 1;

        float length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;

    
        xspeed = dx;
        yspeed = dy;
		ballshooter = true; 
    }
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
* is pressed from the keyboard
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
* */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
	for(int i=0;i<5;i++){
		for(int j=0;j<15;j++)
			cout<<Calpha[i][j]<<' ';
		cout<<endl;
	}
	}
}

/*
* This function is called after every 1000.0/FPS milliseconds
* (FPS is defined on in the beginning).
* You can use this function to animate objects and control the
* speed of different moving objects by varying the constant FPS.
*
* */
	void Timer(int m) {
    if (!gameOver) {
        startingTime++; // Increment the elapsed time
        if (startingTime >= totalTime) {
            gameOver = true; // Set the game over flag after 120 seconds
        }

        // Post a redraw request every 1 second
        glutPostRedisplay();

        // Call the timer function again after 1000ms (1 second)
        glutTimerFunc(1000, Timer, 0);  
    }
}
void FrameRates(int m) {
    // Redraw the screen (update the game state visually)
    glutPostRedisplay();

    // Call the timer function again after 1000ms/60 (approx. 16ms for 60 FPS)
    glutTimerFunc( 1000 / FPS, FrameRates, 0);  
}

	/*
	* our gateway main function
	* */
	int main(int argc, char*argv[]) {
		InitRandomizer(); // seed the random number generator...

		//Dictionary for matching the words. It contains the 370099 words.
		dictionary = new string[dictionarysize]; 
		ReadWords("words_alpha.txt", dictionary); // dictionary is an array of strings
		//print first 5 words from the dictionary
		for(int i=0; i < 5; ++i)
			cout<< " word "<< i << " =" << dictionary[i] <<endl;

		//Write your code here for filling the canvas with different Calphaets. You can use the GetCalphaet function for getting the random Calphaets


		glutInit(&argc, argv); // initialize the graphics library...
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
		glutInitWindowPosition(50, 50); // set the initial position of our window
		glutInitWindowSize(width, height); // set the size of our window
		glutCreateWindow("24i-0058 Word shooter project"); // set the title of our game window
		//SetCanvasSize(width, height); // set the number of pixels...

		// Register your functions to the library,
		// you are telling the library names of function to call for different tasks.
		RegisterTextures();
		glutDisplayFunc(DisplayFunction); // tell library which function to call for drawing Canvas.
		GAB();  // Generate fixed Calphaet grid
		glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
		glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
		glutMouseFunc(MouseClicked);
		glutPassiveMotionFunc(MouseMoved); // Mouse

		//// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
		glutTimerFunc(1000, Timer, 0);
		glutTimerFunc(1000 / FPS, FrameRates, 0);  // Add a timer for rendering
		//// now handle the control to library and it will call our registered functions when
		//// it deems necessary...

		glutMainLoop();
		return 1;
	}
#endif /* */
