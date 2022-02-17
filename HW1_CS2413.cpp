#include <iostream>
#include <vector>

using namespace std;

class CRM {
	protected:
		int etkileyici;
		int satir;
		int newSatir;
		int sutun;
		int deger;
		int counter;
		int n; //The number rows of the original matrix
		int m; //The number of columns of the original matrix
		int nonZeros; //The number of non-zero elements in the original matrix
		int* values; //Array that contains all non-zero values of the matrix, assuming they are all integers
		int* rowPos; //Array that for each row of the original matrix contains the position in the values matrix in which the first non-zero element of this row is stored.
		int* colPos; //Array that contains the column number for each one of the non-zero values in the original matrix.
		//There may be others you may need
		int* colPosNew;
	public:
		CRM ( ); //default or empty constructor
		CRM (int rows, int cols, int numNonZeros);
		int getNumRows ( );
		void addValue (int value); //add a new value in the values array
		void addRow (int row); //add a row number in the rowPos array
		void addColumn (int col);//add a column number in the colPos array
		void display (); //print the contents of the three arrays. Each array must be on a different line (separated by a 
                        //new line character) and you have exactly a single space between each value printed.
		int mostInfluentialUser(); //find the most influential user
		int mostActiveUser(); //find the most active user
		int* influentialUsers (); //compute vector of users ranked by how much influential they are
		int* activeUsers (); //compute vector of users ranked by how much active they are
		~CRM(); //destructor
		//You may define and use any other method you need		
};
//some of the methods – Katia Papakonstantinopoulou
CRM::CRM ( ) {
	n = 0;
	m = 0;
	values = NULL;
	rowPos = NULL;
	colPos = NULL;
}
CRM::CRM (int rows, int cols, int numNonZeros) {
	n = rows;
	m = cols;
	nonZeros = numNonZeros;
	values = new int [nonZeros];
	rowPos = new int [n];
	colPos = new int [nonZeros];
	colPosNew = new int [nonZeros];
	satir = 0;
	newSatir =0;
	sutun = 0;
	deger = 0;
	counter=0;
	etkileyici = 0;
	
}
//Ben yazdim
int CRM::getNumRows() { 
	return n; 
}
void CRM::addValue(int value){
	
	values[deger] = value;
	deger++;	
}
void CRM::addRow (int row){
	rowPos[0] = 0;
	if(satir == row){
		counter++;
	}else{
		satir++;
		if(satir == row){
			rowPos[satir] = counter;
		    counter++;
		}else{
			rowPos[satir] = -1;
			satir++;
			rowPos[satir] = counter;
			counter++;
		}	
	}
	
}
void CRM::addColumn (int col){
	
	colPos[sutun] = col;
	sutun++;
}
void CRM::display (){
	cout<<"values: ";
	for(int i=0; i<nonZeros; i++){
		cout<<values[i]<<" ";
	}
	cout<<"\n";
	cout<<"rowPos: ";
	for(int i=0; i<n; i++){
		cout<<rowPos[i]<<" ";
	}
	cout<<"\n";
	cout<<"colPos: ";
	for(int i=0; i<nonZeros; i++){
		cout<<colPos[i]<<" ";
	}
	cout<<"\n";
	cout<<"\n";
}


int CRM::mostInfluentialUser(){
//fill in the code
	int sum=0;
	
	int numara=0;
	for(int i=0;i<n; i++){
		int toplam=0;
		for (int j = 0; j < nonZeros; j++)
		{
			if(i == colPos[j]){
				toplam=toplam + values[j];
			}
		}
		if(toplam>sum){
				sum=toplam;
				numara = i;
		}
	}
	return numara;
};
int CRM::mostActiveUser(){
	int indexTutucu =0;
	int toplam =0;
	int* rowPosArray = new int[n+1];
	
	for(int i =0;i<n;i++){
		rowPosArray[i]=rowPos[i];
	}
	rowPosArray[n] = nonZeros;
	
	for(int i=0;i<n;i++){
		int sum=0;
		int start=rowPosArray[i];
		int end =rowPosArray[i+1];
		if(rowPosArray[i+1] ==-1){
			end=rowPosArray[i+2];
		}
		if(rowPosArray[i]==-1){
			start=rowPosArray[i+1];
		}
		for(int index = start; index<end;index++){
			sum +=values[index];
			
		}
		
		if(sum>toplam){
			toplam = sum;
			
			indexTutucu = i;
		}
	}

	return indexTutucu;
    
	
}
int* CRM::activeUsers (){
	int* outputVector = new int [n];
	int* valueVector = new int[n];
	int* indexVector = new int[n];


	
	int* rowPosArray = new int[n+1];
	
	for(int i =0;i<n;i++){
		rowPosArray[i]=rowPos[i];
	}
	rowPosArray[n] = nonZeros;
	
	for(int i=0;i<n;i++){
		int sum=0;
		int start=rowPosArray[i];
		int end =rowPosArray[i+1];
		if(rowPosArray[i+1] ==-1){
			end=rowPosArray[i+2];
		}
		if(rowPosArray[i]==-1){
			start=rowPosArray[i+1];
		}
		for(int index = start; index<end;index++){
			sum +=values[index];
			
		}
		valueVector[i]= sum;
		indexVector[i]=i;
	}
	
	for(int index = 0; index<n; index++){
		int toplam = 0;
		int siralama = 0;
		
		for(int yeni = 0; yeni<n; yeni++){
			if(valueVector[yeni]>toplam){
				toplam =valueVector[yeni];
				siralama = yeni;
			}
		}
		outputVector[index] = siralama;
		valueVector[siralama]=-1;	
	}
	int counter=0;
	for(int index= 0; index<n; index++){
		if(valueVector[index] ==-1) {
			counter++;
		}
	}
	
	for(int yeni=0;yeni<n; yeni++){
			if(valueVector[yeni]==0){
				outputVector[counter] = yeni;
				valueVector[yeni]=-1;
				counter++;
			}
		}
	return outputVector;
}

int* CRM::influentialUsers (){
	int* outputVector = new int [n];
	int* indexVector = new int[n];
	for(int i = 0; i<n;i++){
		indexVector[i] =i;
	}
	int* valueVector = new int[n];
	int* controlVector = new int[n];
	
	
	
	for (int i=0; i < m; i++){
		int toplam =0;
		for(int j =0; j<nonZeros; j++){
			if(colPos[j] == i){
				toplam += values[j];
			}
		}
		valueVector[i]=toplam;
		controlVector[i]=toplam;
	}
	 
	for(int index = 0; index<n; index++){
		int toplam = 0;
		int siralama = 0;
		
		for(int yeni = 0; yeni<n; yeni++){
			if(valueVector[yeni]>=toplam){
				toplam =valueVector[yeni];
				siralama = yeni;
			}
		}
		
		outputVector[index] = siralama;
		valueVector[siralama]=-1;
	}
	
	int ilk;
	int son;
	for(int index=0; index<n-1;index++){
		for(int j=index+1;j<n;j++){
			if(controlVector[index] == controlVector[j]){
				if(index>j){
					ilk = index;
					son = j;
				}else{
					ilk=j;
					son=index;
				}
				break;
		    }
		}
	}
	for(int index=0; index<n; index++){
		if(outputVector[index] == ilk){
			int temp = outputVector[index];
			outputVector[index]=outputVector[index+1];
			outputVector[index+1] =temp;
			break;	
		}
	}
	return outputVector;	
}


CRM::~CRM ( ) {
	if (values != NULL) delete [ ] values;
	if (rowPos != NULL) delete [ ] rowPos;
	if (colPos != NULL) delete [ ] colPos;
	cout << "CRM Object Destroyed!!" << endl;
	n = 0;
	m = 0;
	nonZeros = 0;
}


#include <iostream>
using namespace std;

//write the entire CRM class here with all the methods

int main ( ) {

   CRM* A;
   int numRows, numColumns, numNonZeros;
   int row, col, value;

   //read in the first matrix

   cin >> numRows >> numColumns;
   cin >> numNonZeros;
   

    A = new CRM (numRows, numColumns, numNonZeros);
   for (int i=0; i < numNonZeros; i++) {//ekleme yaptim
	cin >> row >> col >> value;
	(*A).addValue (value);
	(*A).addRow (row);//needs to be done cleverly in the method
	(*A).addColumn (col);
   }
   (*A).display ( );

//Find most influential user
	int mostInf = (*A).mostInfluentialUser ();
	cout << "Most influential user: " << mostInf << endl;
	cout << endl;

//Find most active user
	int mostAct = (*A).mostActiveUser();//ekleme yaptim
	cout << "Most active user: " << mostAct << endl;
	cout << endl;

//Rank users based on how much influential they are
    int* influentialityVector = (*A).influentialUsers ();
	//cout << "Users ranked by Influentiality: " << endl;
	cout << "Users ranked by Influentiality: ";
    for (int i=0; i < (*A).getNumRows ( ); i++) 
		cout << influentialityVector [i] << " ";
    cout << endl << endl;

//Rank users based on how much active they are
//fill-in code
    int* activityVector = (*A).activeUsers ();//ben yazdim
	//cout << "Users ranked by Activity: " << endl;
	cout << "Users ranked by Activity: ";
    for (int i=0; i < (*A).getNumRows ( ); i++) 
		cout << activityVector [i]<< " ";//ben yazdim
    cout << endl;

// Call the destructors
     delete A;
     delete [ ] influentialityVector;
     delete [ ] activityVector; 

   return 0;
}
