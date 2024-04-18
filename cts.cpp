#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class pin{
    public:
        int num, x, y;
        pin(int num, int x, int y){
            this->num=num;
            this->x=x;
            this->y=y;
        }
};
class tap{
    public:
        int num, x, y;
        tap(int num, int x, int y){
            this->num=num;
            this->x=x;
            this->y=y;
        }
};
int manhattan_distance(int x1, int y1, int x2, int y2){
    return (abs(x1-x2)+abs(y1-y2));
}

int main(int argc, char * argv[]){
    if (argc < 2 || argc > 3) {
        cout<<"usage: reduce <in_file> <out_file>"<<endl;
        exit(1);
    }
    char * inFile = argv[1];
    char * outFile = argv[2];
    string info_type;
    ifstream in(inFile);    //input filestream
    ofstream out(outFile);  //output filestream
    
    int max_runtime, max_load, grid_size, capacity, temp_num, temp_x, temp_y, num_pins, num_taps;
    vector<pin *> pins;
    vector<tap *> taps;
    
    /* read the input file */
    while(in>>info_type){
        if (info_type=="MAX_RUNTIME"){
            in>>max_runtime;
        } else if (info_type=="MAX_LOAD"){
            in>>max_load;
        } else if (info_type=="GRID_SIZE"){
            in>>grid_size;
        } else if (info_type=="CAPACITY"){
            in>>capacity;
        } else if (info_type=="PINS"){
            in>>num_pins;
        } else if (info_type=="PIN"){
            in>>temp_num;
            in>>temp_x;
            in>>temp_y;
            pins.push_back(new pin(temp_num, temp_x, temp_y));
        } else if (info_type=="TAPS"){
            in>>num_taps;
        } else if (info_type=="TAP"){
            in>>temp_num;
            in>>temp_x;
            in>>temp_y;
            taps.push_back(new tap(temp_num, temp_x, temp_y));
        }
    }
    in.close();

    /* compute the distance table */
    vector<vector<int> > pin_d;
    vector<int> temp_vec;
    vector<int> curr_load_remain(num_taps, max_load);
    for (int i=0;i<num_pins;i++){
        for (int j=0;j<num_taps;j++){
            temp_vec.push_back(manhattan_distance(pins.at(i)->x,pins.at(i)->y,taps.at(j)->x,taps.at(j)->y));
        }
        pin_d.push_back(temp_vec);
        temp_vec.clear();
    }
    for (int i=0;i<curr_load_remain.size();i++){
        cout<<"load_tap"<<i<<": "<<curr_load_remain.at(i)<<endl;
    }
    for (int i=0;i<pin_d.size();i++){
        cout<<"pin"<<i<<" :";
        for (int j=0;j<pin_d.at(0).size();j++){
            cout<<pin_d.at(i).at(j)<<" ";
        }
        cout<<endl;
    }

    /* debug info just from the input file */
    cout<<endl;
    cout<<"debug_info----------------------------------------------------"<<endl;
    cout<<"max_runtime: "<<max_runtime<<endl;
    cout<<"max_load: "<<max_load<<endl;
    cout<<"grid_size: "<<grid_size<<endl;
    cout<<"capacity: "<<capacity<<endl;
    cout<<"pins: "<<num_pins<<endl;
    for (int i=0;i<num_pins;i++){
        cout<<"pin"<<i<<": "<<pins.at(i)->x<<" "<<pins.at(i)->y<<endl;
    }
    cout<<"taps: "<<num_taps<<endl;
    for (int i=0;i<num_taps;i++){
        cout<<"tap"<<i<<": "<<taps.at(i)->x<<" "<<taps.at(i)->y<<endl;
    }
    out.close();
}
