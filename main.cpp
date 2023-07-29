#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct district {
    string name;
    string type;
    int num_resident;
    double power;
    bool has_power;
    int num_technician;
    string technicians[10];
};



void load(string fname, district districts[], int &num, int &power){
  ifstream infile(fname);
  infile >> power;
  infile >> num;
  infile.ignore();
  
  for (int i = 0; i < num; i++){
    getline(infile, districts[i].name);
    infile >> districts[i].type;
    infile >> districts[i].num_resident;
    infile >> districts[i].power;
    infile >> districts[i].has_power;
    infile >> districts[i].num_technician;
    infile.ignore();
    if (districts[i].num_technician > 0){
      for (int j = 0; j < districts[i].num_technician; j++){
        getline(infile, districts[i].technicians[j]);
      }
    }
  }

  std::sort(districts, districts + num, [](const district &a, const district &b) {
    return a.num_resident < b.num_resident;
  });
}


void save(string fname, district districts[], int num, int power) {
    ofstream outfile(fname);
    outfile << power << endl;
    outfile << num << endl;
    for (int i = 0; i < num; i++) {
        outfile << districts[i].name << endl;
        outfile << districts[i].type << endl;
        outfile << districts[i].num_resident << endl;
        outfile << districts[i].power << endl;
        outfile << districts[i].has_power << endl;
        outfile << districts[i].num_technician << endl;
        for (int j = 0; j < districts[i].num_technician; j++) {
            outfile << districts[i].technicians[j] << endl;
        }
    }
    outfile.close();
}

void print_all(district districts[], int num, int power) {
    int total_demand = 0;
    for (int i = 0; i < num; i++) {
    }
    cout << "The current power supply is " << power << "MW.\n";
    for (int i = 0; i < num; i++) {
        cout << districts[i].name << endl;
        cout << "District type: " << districts[i].type << endl;
        cout << "Number of residents: " << districts[i].num_resident << endl;
        if (districts[i].has_power == false) {
            cout << "Power use: 0MW" << endl;
        } else {
          total_demand += districts[i].power;
            cout << "Power use: " << districts[i].power << "MW" << endl;
        }
        cout << "Has power: " << districts[i].has_power << endl;
        if (districts[i].num_technician > 0) {
            cout << "Technicians: ";
            for (int j = 0; j < districts[i].num_technician; j++) {
                cout << districts[i].technicians[j];
                if (j != districts[i].num_technician - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "---" << endl;
    }
    if (total_demand > power) {
        cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << total_demand << "MW of power demand. Please shut off one or more districts.\n";
        cout << "---" << endl;
    }
}


void assign_technician(string tech_name, string district_name, district districts[], int num_district) {
    for (int i = 0; i < num_district; i++) {
        if (districts[i].name == district_name) {
            int num_technicians = districts[i].num_technician;
            districts[i].technicians[num_technicians] = tech_name;
            districts[i].num_technician++;
            cout << "Technician assigned!" << endl;
            return;
        }
    }
    cout << "Error! The district with that name doesn't exist." << endl;
}

void cut_power(string district_name, district districts[], int num_districts) {
  int count = 0;
    for (int i = 0; i < num_districts; i++) {
        if (districts[i].name == district_name) {
            districts[i].has_power = false;
          count = 1;
          }
      }
  if( count == 1){
                cout << "The district's power has been successfully turned off." << endl;
            } else {
                cout << "Error! The district with that name doesn't exist.\n";
    }
  }

void restore_power(string district_name, district districts[], int num_districts) {
  int count = 0;
    for (int i = 0; i < num_districts; i++) {
        if (districts[i].name == district_name) {
            districts[i].has_power = true;
          count = 1;
          }
      }
  if( count == 1){
                cout << "The district's power has been successfully turned back on." << endl;
            } else {
                cout << "Error! The district with that name doesn't exist.\n";
    }
  }

int main() {
    string file_name;
    int option;
    cout << "Please enter the name of the file to load:" << endl;
    district districts[10];
    int num_districts = 0, total_power = 0;

    // Ask user for file name and load file
    cin >> file_name;
    load(file_name, districts, num_districts, total_power);

    // Print all district information
    print_all(districts, num_districts, total_power);

    
    bool exit_program = false;

    while (!exit_program) {
    // Print the main menu
    cout << "Main Menu\n";
    cout << "1- Status\n";
    cout << "2- Set Power Supply\n";
    cout << "3- Shutoff Power\n";
    cout << "4- Restore Power\n";
    cout << "5- Assign Technician\n";
    cout << "6- Save\n";
    cout << "7- Load\n";
    cout << "8- Exit\n";
    cout << "Please enter your choice:\n";
      cin >> option;

       switch (option) {
    case 1:
        print_all(districts, num_districts, total_power);
        break;
    case 2:
        cout << "Enter the updated power supply in megawatts:" << endl;
        cin >> total_power;
        break;
    case 3:
        // Shutoff Power
        {
            string district_name;
            cout << "Enter the name of the district:" << endl;
          cin.ignore();
            getline(cin, district_name);
            cut_power(district_name, districts, num_districts);
        }
        break;
    case 4:
        // Restore Power
        {
            string district_name;
            cout << "Enter the name of the district:" << endl;
            cin.ignore();
            getline(cin, district_name);
            restore_power(district_name, districts, num_districts);
        }
        break;
    case 5: {
        string tech_name, district_name;
        cout << "Enter the name of the technician:" << endl;
        cin.ignore();
        getline(cin, tech_name);
        cout << "Enter the name of the district to assign them to:" << endl;
        getline(cin, district_name);
        assign_technician(tech_name, district_name, districts, num_districts);
        break;
    }
    case 6: {
        string save_file_name;
        cout << "Enter the file name to save to:";
        cin.ignore();
        getline(cin, save_file_name);
        save(save_file_name, districts, num_districts, total_power);
        cout << "Data has been successfully saved to " << save_file_name << ".\n";
        break;
    }
    case 7: {
        string load_file_name;
        cout << "Enter the file name to load from: ";
        cin.ignore();
        getline(cin, load_file_name);
        load(load_file_name, districts, num_districts, total_power);
        break;
    }
    case 8:
        exit_program = true;
        break;
    default:
        cout << "Invalid Option!" << endl;
        break;
}
      }
  }


