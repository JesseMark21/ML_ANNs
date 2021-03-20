#include <istream>
#include <iostream>
#include <fstream>
using namespace std;

struct perceptron{
    float w1Ptr = 1.0;
    float w2Ptr = 1.0;

    float perc(float x1, float x2, float threshold){
        return x1*w1Ptr + x2*w2Ptr >= threshold ? 1.0 : 0.0;
    }

    float changeW(float t, float o, float learnR){
        return learnR*(t-o);
    }

    perceptron trainP(perceptron p, float x1, float x2, float target, float threshold, float learningRate){
        float output;
        output = p.perc(x1, x2, threshold);

        float deltaW;
        deltaW = changeW(target, output, learningRate);

        //cout << "w1 " << p.w1Ptr << endl;
        //cout << "w2 " << p.w2Ptr << endl;

        p.w1Ptr += deltaW*x1;
        p.w2Ptr += deltaW*x2;

        //cout << "updated w1 " << p.w1Ptr << endl;
        //cout << "updated w2 " << p.w2Ptr << endl;
        
        return p;
    }

};

int main(int arfc, char** argv){
    
    ofstream myfile;
    myfile.open("Output.txt");

    float learningRate = 0.3;
    float threshold = 0.5;

    float trainingData[4][2];
    float bias = 1;
    

    //{1,1}
    trainingData[1][0] = 1.0;
    trainingData[1][1] = 1.0;

    //{1,0}
    trainingData[0][0] = 1.0;
    trainingData[0][1] = 0.0;

    //{0,1}
    trainingData[2][0] = 0.0;
    trainingData[2][1] = 1.0;

    //{0,0}
    trainingData[3][0] = 0.0;
    trainingData[3][1] = 0.0;

    float trainingResult[4];
    trainingResult[0] = 0.0;
    trainingResult[1] = 1.0;
    trainingResult[2] = 1.0;
    trainingResult[3] = 0.0;

    float andData[4][2] = {
                            {0.0, 0.0},
                            {0.0, 1.0},
                            {1.0, 0.0},
                            {1.0, 1.0}
                            };

    float andResult[4];
    andResult[0] = 0.0;
    andResult[1] = 0.0;
    andResult[2] = 0.0;
    andResult[3] = 1.0;

    float nandData[4][2] = {
                            {0.0, 0.0},
                            {0.0, 1.0},
                            {1.0, 0.0},
                            {1.0, 1.0}
                            };

    float nandResult[4];
    nandResult[0] = 1.0;
    nandResult[1] = 1.0;
    nandResult[2] = 1.0;
    nandResult[3] = 0.0;

    float orData[4][2] = {
                            {0.0, 0.0},
                            {1.0, 0.0},
                            {0.0, 1.0},
                            {1.0, 1.0}
                            };

    float orResult[4];
    orResult[0] = 0.0;
    orResult[1] = 1.0;
    orResult[2] = 1.0;
    orResult[3] = 1.0;
  
    bool error = true;
    perceptron OR;
    perceptron NAND;
    perceptron AND;
    int counter =0;

    int numberIterations = 0;
    while(error){
        numberIterations ++;
        //OR
        float input[2]; 
        input[0] = orData[counter][0];
        input[1] = orData[counter][1];

        float target;
        target = orResult[counter];
        
        //cout << "OR: ______________________________" << endl;
        OR = OR.trainP(OR, input[0], input[1], target, threshold, learningRate);


        //NAND
        input[0] = nandData[counter][0];
        input[1] = nandData[counter][1];

        
        target = nandResult[counter];
        
        NAND = NAND.trainP(NAND, input[0], input[1], target, threshold, learningRate);

        //AND
        input[0] = andData[counter][0];
        input[1] = andData[counter][1];

        target = andResult[counter];

        //cout << "AND: ______________________________" << endl;
        AND = AND.trainP(AND, input[0], input[1], target,threshold, learningRate);

        error = false;
        for(int i = 0; i<4; i++){
            //Test for error
            float x1 = trainingData[i][0];
            float x2 = trainingData[i][1];

            //OR
            float orOutput;
            orOutput = OR.perc(x1, x2, threshold);
            //NAND
            float nandOutput;
            nandOutput = NAND.perc(x1, x2, threshold);
            
            //AND
            float andOutput;
            andOutput = AND.perc(orOutput, nandOutput, threshold);
            
            if(andOutput != trainingResult[i]){
                error = true;
            }
        }
        

        counter++;
        if(counter == 4){
            counter = 0;
        }
    }

    myfile << "Q1: 3" << endl; 
    myfile << "(x1, x2) -> OR perceptron -> ORresult" << endl;
    myfile << "(x1, x2) -> NAND perceptron -> NANDresult" << endl; 
    myfile << "(ORresult, NANDresult) -> AND perceptron -> final result" << endl;
    myfile << endl;
    myfile << "Q2: " << numberIterations << endl; 
}



