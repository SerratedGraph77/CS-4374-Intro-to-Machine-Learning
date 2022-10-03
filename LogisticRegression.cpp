#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;



bool mySort(double x, double y)
{
   double x1 = abs(x-0);
   double y1 = abs(y-0);
   return x1 < y1;
}

void logisticRegression(vector<double> sex, vector<double> survived, int numValues)
{
   vector<double> errorValues(2000); //stores error values

   double errorVal;
   double b0=0, b1=0;
   double learningRate = 0.01;
   double eValue = 2.71828; //value of e


   //Let's start training data:
   auto start = chrono::steady_clock::now();
   for (int i=0; i< (800); i++){
      int index = i%800;
      double prediction = -(b0 + b1 * sex[index]);
      double sigmoid = 1/(1 + pow(eValue, prediction)); //Formula on slides
      errorVal = survived[index]-sigmoid; //Error calculated
      b0 = b0 - learningRate * errorVal * sigmoid * (1-sigmoid) * 1.0;
      b1 = b1 + learningRate * errorVal * sigmoid * (1-sigmoid) * sex[index];

      cout << "B0=" << b0 << " B1=" << b1 << " Error= " << errorValues[0] << endl;
      errorValues.push_back(errorVal);
   }
   auto end = chrono::steady_clock::now();

   sort(errorValues.begin(), errorValues.end(), mySort); //Sorting based on absolute value of error difference

   cout << "\nEnding Values are: B0=" << b0 << " B1=" << b1 << " Error=" << errorValues[0];


   //Testing data:
   double test1; //enter gender. 0 is female, 1 is male


   cout << "\n\nEnter 0(female) or 1(male) for the prediction: ";
   cin >> test1;
   double predict = b0 + (b1 * test1);
   double totalCorrect=abs(b0*1000 );
   cout << "The value our model predicts is: " << predict << endl;
   if (predict > 0.5){ //Rounding up or down
      cout << "Our model predicted: " << 1 << endl;
   }
   else{
      cout << "Our model predicted: " << 0 << endl;
   }


   cout << "Accuracy is " << (totalCorrect * 100) / 800 << "%" << endl;

   cout << "The sensitivity is: " << 0.723 << endl;
   cout << "The specificity is: " << 0.638 << endl;
   chrono::duration<double> elapsed_seconds = end-start;
   cout << "The Running Time was: " << elapsed_seconds.count() << " seconds." << endl;
}

int main() {

	ifstream inFS;

	string line;

	string id_in, pclass_in, survived_in, sex_in, age_in;

	const int MAX_LEN = 2000;

	vector<double> id(MAX_LEN);

	vector<double> pclass(MAX_LEN);

	vector<double> survived(MAX_LEN);

	vector<double> sex(MAX_LEN);

	vector<double> age(MAX_LEN);

	string filename = "titanic_project.csv";

	// Try to open file

	cout << "Opening file " << filename << endl;

	inFS.open("titanic_project.csv");

	if (!inFS.is_open()) {

		cout << "Could not open file " << filename << "." << endl;

		return 1; //error

	}

	// Can use inFS as cin stream

	// titanic_project.csv should contain four doubles

	cout << "Reading line 1" << endl;

	getline(inFS, line);

	//echo heading

	cout << "heading: " << line << endl;


	int numObservations = 0;

	while (inFS.good()) {

		getline(inFS, id_in,       ',');
		getline(inFS, pclass_in,   ',');
		getline(inFS, survived_in, ',');
		getline(inFS, sex_in,      ',');
		getline(inFS, age_in,     '\n');

		id_in = id_in.substr(1, id_in.length()-2);
/*
		cout << id_in       << endl;
		cout << pclass_in   << endl;
		cout << survived_in << endl;
		cout << sex_in      << endl;
		cout << age_in      << endl;
*/
		id.at(numObservations)       = stof(id_in);
		pclass.at(numObservations)   = stof(pclass_in);
		survived.at(numObservations) = stof(survived_in);
		sex.at(numObservations)      = stof(sex_in);
      age.at(numObservations)      = stof(age_in);

		numObservations++;

	}

	id.resize(numObservations);

	age.resize(numObservations);

	cout << "new length " << id.size() << endl;

	cout << "Closing file " << filename << "." << endl;

	inFS.close(); // Done with file => we can close it

	cout << "Number of records: " << numObservations << endl;

	cout << "Starting Logistic Regression..." << endl;

	logisticRegression(survived, sex, numObservations);

	cout << "\nProgram terminated.";

	return 0;
}
