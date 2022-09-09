#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>


using namespace std;

double find_mean(vector<double> vect) {
	if (vect.empty()) {
		return 0;
	}

	double mean = accumulate(vect.begin(), vect.end(), 0.0) / vect.size(); // Divide the sum by the size (# of variables)
	return mean;
}

double covar(vector<double> vect1, vector<double> vect2){

	double mean_vect1 = find_mean(vect1);
	double mean_vect2 = find_mean(vect2);
	double sum = 0;
	size_t size = vect1.size();

	for (int i = 0; i < size; i++) {
		sum += (vect1.at(i) - mean_vect1) * (vect2.at(i) - mean_vect2);
	}

	return sum / (size - 1);
}

double find_sum(vector<double> vect) {
	
	if (vect.empty()) {
		return 0;
	}

	double sum = accumulate(vect.begin(), vect.end(), 0.0); // Calculate the sum
	return sum;
}

double cor(vector<double> x, vector<double> y) {

	size_t size = x.size();
	int x_sum = 0, y_sum = 0, xy_sum = 0;
	int x_squareSum = 0, y_squareSum = 0;

	x_sum = find_sum(x);
	y_sum = find_sum(y);

	for (int i = 0; i < size; i++) {
		xy_sum = xy_sum + x.at(i) * y.at(i);

		x_squareSum = x_squareSum + x.at(i) * x.at(i);
		y_squareSum = y_squareSum + y.at(i) * y.at(i);
	}

	double correlation = (double)(size * xy_sum - x_sum * y_sum) / sqrt((size * x_squareSum - x_sum * x_sum) * (size * y_squareSum - y_sum * y_sum));

	return correlation;

}

double find_median(vector<double> vect) {
	if (vect.empty()) {
		return 0;
	}
	
	sort(vect.begin(), vect.end());
	double median = vect.at(vect.size() / 2);
	return median;
}

double find_range(vector<double> vect) {
	if (vect.empty()) {
		return 0;
	}
	
	double max = *max_element(vect.begin(), vect.end()); // Find the largest element
	double min = *min_element(vect.begin(), vect.end()); // Find the smallest element

	double range = max - min; // Range is the difference between the two
	
	return range;
}

void print_stats(vector<double> am){
	cout << "Sum = "    << find_sum   (am) << endl;
	cout << "Mean = "   << find_mean  (am) << endl;
	cout << "Median = " << find_median(am) << endl;
	cout << "Range = "  << find_range (am) << endl;
}

int main(int argc, char** argv) {

	ifstream inFS;
	string line;
	string rm_in, medv_in;
	const int MAX_LEN = 1000;
	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);

	string filename = "Boston.csv";
	// Try to open file
	cout << "Opening file " << filename << endl;

	inFS.open("Boston.csv");
	if (!inFS.is_open()) {
		cout << "Could not open file " << filename << "." << endl;
		return 1; //error
	}

	// Can use inFS as cin stream
	// Boston.csv should contain two doubles

	cout << "Reading line 1" << endl;
	getline(inFS, line);

	//echo heading
	cout << "heading: " << line << endl;

	int numObservations = 0;
	while (inFS.good()) {

		getline(inFS, rm_in, ',');
		getline(inFS, medv_in, '\n');

		rm.at(numObservations)   = stof(rm_in);
		medv.at(numObservations) = stof(medv_in);

		numObservations++;
	}

	rm.resize(numObservations);
	medv.resize(numObservations);

	cout << "new length " << rm.size() << endl;

	cout << "Closing file " << filename << "." << endl;
	inFS.close(); // Done with file => we can close it

	cout << "Number of records: " << numObservations << endl;

	cout << "\nStats for rm" << endl;
	print_stats(rm);

	cout << "\nStats for medv" << endl;
	print_stats(medv);

	cout << "\nCovariance = "  << covar(rm, medv) << endl;

	cout << "\Correlation = " << cor(rm, medv)   << endl;

	cout << "\nProgram terminated.";

	return 0;
}
