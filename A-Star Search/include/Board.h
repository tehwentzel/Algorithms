#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <stdlib.h>
#include <memory>

class Board
{
    public:
        std::vector< std::vector<int> > daboard;
        int bsize;
        int hscore;
        int mscore;
        int dist;
        std::shared_ptr<Board> parent;

        Board(std::string dafile){
            std::ifstream file;
            file.open(dafile);
            file >> bsize;
            for(int k = 0; k != bsize; k++){
                std::vector<int> row;
                for(int n = 0; n != bsize; n++){
                    int temp;
                    file >> temp;
                    row.push_back(temp);
                }
                daboard.push_back(row);
            }
            mscore = this -> manhattan();
            hscore = this -> hamming();
            dist = 0;
            parent = nullptr;
        }

        Board(const Board & b){
            daboard = b.daboard;
            bsize = b.bsize;
            hscore = b.hscore;
            mscore = b.mscore;
            dist = b.dist;
            parent = b.parent;
        }

        int dimension(){ return bsize; };  //I should change these to capitol to follow proper coding style

        friend std::ostream &operator<<( std::ostream &output, const Board &theboard){
            for(auto &row: theboard.daboard){
                for(auto &val: row){
                    output << val << " ";
                }
                output << std::endl;
            }
            return(output);
        }

        int hamming(){
            hscore = 0;
            for(int row = 0; row != bsize; row++){
                for(int col = 0; col != bsize; col++){
                    if( daboard[row][col] != ((row*bsize)+(col+1))%(bsize*bsize)){ //because weird math is better than handling edge cases
                        hscore++;
                    }
                }
            }
            return(hscore);
        }

        void setDist(int d){
            dist = d;
        }

        int manhattan(){
            mscore = 0;
            for(int row = 0; row != bsize; row++){
                for(int col = 0; col != bsize; col++){
                    auto bnum = daboard[row][col];
                    if(bnum == 0){ bnum = bsize*bsize; }  //I can't thing of a better way to do edge cases;
                    mscore = mscore + abs(((bnum-1)/bsize - row));
                    mscore = mscore + abs(( bnum - ((bnum-1)/bsize)*bsize ) - (col+1)); // this makes no sense but works for the one test case except for the 0/9
                    }
                }
            return(mscore);
        }

        bool isGoal(){
            hscore = this -> hamming();
            mscore = this -> manhattan();
            return( ((hscore == 0 && mscore == 0)? true:false) );
        }

        bool operator==(Board &b){
            if(bsize != b.dimension()) {return(false);}
            for(int row = 0; row != bsize; row++){
                for(int col = 0; col != bsize; col++){
                    if( daboard[row][col] != b.daboard[row][col] ){ return(false); }
                }
            }
            return(true);
        }

        bool operator==(Board &&b){
            if(bsize != b.dimension()) {return(false);}
            for(int row = 0; row != bsize; row++){
                for(int col = 0; col != bsize; col++){
                    if( daboard[row][col] != b.daboard[row][col] ){ return(false); }
                }
            }
            return(true);
        }

        Board twin(){
            Board dummy(*this);
            int r1 = -1;
            int r2 = -1;
            int c1 = -1;
            int c2 = -1;
            for(int row = 0; row != bsize; row++){
                if(r1 != -1 && r2 != -1){ break; }
                for(int col = 0; col != bsize; col++){
                    if(r1 != -1 && daboard[row][col] != 0){
                        r2 = row;
                        c2 = col;
                        break;
                       }
                    else if(r1 == -1 && daboard[row][col] != 0){
                        r1 = row;
                        c1 = col;
                    }
                }
            }
            dummy.daboard[r1][c1] = daboard[r2][c2];
            dummy.daboard[r2][c2] = daboard[r1][c1];
            dummy.mscore = dummy.manhattan();
            dummy.hscore = dummy.hamming();
            return(dummy);
        }


        void setParent(std::shared_ptr<Board> b){
            parent = b;
        }

        std::vector< std::shared_ptr<Board> > Neighbors(){
            std::vector< std::shared_ptr<Board> > naybors;
            Board clone(*this);

            int r = 0;
            int c = 0;

            for(auto row = 0; row != bsize; row++){
                for(auto col = 0; col != bsize; col++){
                    if(clone.daboard[row][col]==0){
                        r = row;
                        c = col;
                        break;
                    }
                }
            }

            if(r - 1 >= 0){
                std::shared_ptr<Board> tempboard1 = std::make_shared<Board>(clone);
                (*tempboard1).daboard[r][c] = clone.daboard[r-1][c];
                (*tempboard1).daboard[r-1][c] = 0;
                naybors.push_back(tempboard1);
                }
            if(c - 1 >= 0){
                std::shared_ptr<Board> tempboard2 = std::make_shared<Board>(clone);
                (*tempboard2).daboard[r][c] = clone.daboard[r][c-1];
                (*tempboard2).daboard[r][c-1] = 0;
                naybors.push_back(tempboard2);
                }
            if(r + 1 < bsize){
                std::shared_ptr<Board> tempboard3 = std::make_shared<Board>(clone);
                (*tempboard3).daboard[r][c] = clone.daboard[r+1][c];
                (*tempboard3).daboard[r+1][c] = 0;
                naybors.push_back(tempboard3);
                }
            if(c + 1 < bsize){
                std::shared_ptr<Board> tempboard4 = std::make_shared<Board>(clone);
                (*tempboard4).daboard[r][c] = clone.daboard[r][c+1];
                (*tempboard4).daboard[r][c+1] = 0;
                naybors.push_back(tempboard4);
                }
            return(naybors);
        }

        virtual ~Board(){};

    protected:

    private:
};

struct Mcompare
{
    bool operator()(std::shared_ptr<Board> a, std::shared_ptr<Board> b){ return ((*b).manhattan() + (*b).dist < (*a).manhattan() + (*a).dist); };
};

#endif // BOARD_H
