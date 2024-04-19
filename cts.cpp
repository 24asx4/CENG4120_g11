#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
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

bool vec_contain(vector<int> vec, int target){
    for (int i=0;i<vec.size();i++){
        if (vec.at(i)==target){
            return true;
        }
    }
    return false;
}
int best_tap(vector<int> pin, vector<int> tap){
    int max=-1;
    int max_index=-1;
    for (int i=0;i<pin.size();i++){
        if (tap.at(pin.at(i))>max){
            max=tap.at(pin.at(i));
            max_index=i;
        }
    }
    return max_index;
}
int manhattan_distance(int x1, int y1, int x2, int y2){
    return (abs(x1-x2)+abs(y1-y2));
}

int main(int argc, char * argv[]){
    /* measure time (start) */
    int start = clock();
    if (argc < 5 || argc > 5) {
        cout<<"usage: cts --input <in_file> --output <out_file>"<<endl;
        exit(1);
    }
    char * inFile;
    char * outFile;
    if (strcmp(argv[1],"--input")==0){
        inFile = argv[2];
    } else{
        cout<<"usage: cts --input <in_file> --output <out_file>"<<endl;
        exit(1);
    }
    if (strcmp(argv[3],"--output")==0){
        outFile = argv[4];
    } else{
        cout<<"usage: cts --input <in_file> --output <out_file>"<<endl;
        exit(1);
    }

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
    /* print the table (debug only) */
    /*
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
    */
    /* run the alg */
    vector<int> max_dis_pin;
    vector<int> min_dis_pin;
    vector<int> done;
    vector<vector <int> > pin_to_tap(num_taps);
    vector<int> full_load;
    
    while (done.size()<num_pins){
        int max_dis=-1;
        for (int i=0;i<pin_d.size();i++){
            if (vec_contain(done,i)){
                continue;
            }
            for (int j=0;j<pin_d.at(0).size();j++){
                if (pin_d.at(i).at(j)>max_dis){
                    max_dis_pin.clear();
                    max_dis=pin_d.at(i).at(j);
                    if (!vec_contain(max_dis_pin, i)){
                        max_dis_pin.push_back(i);
                    }
                } else if (pin_d.at(i).at(j)==max_dis){
                    if (!vec_contain(max_dis_pin, i)){
                        max_dis_pin.push_back(i);
                    }
                }
            }
        }

        for (int i=0;i<max_dis_pin.size();i++){
            int min_dis=9999999;
            for (int j=0;j<pin_d.at(0).size();j++){
                if (vec_contain(full_load, j)){
                    continue;
                }
                if (pin_d.at(max_dis_pin.at(i)).at(j)<min_dis){
                    min_dis_pin.clear();
                    min_dis=pin_d.at(max_dis_pin.at(i)).at(j);
                    min_dis_pin.push_back(j);
                } else if (pin_d.at(max_dis_pin.at(i)).at(j)==min_dis){
                    min_dis_pin.push_back(j);
                }
            }
            if (min_dis_pin.size()<=1){
                pin_to_tap.at(min_dis_pin.at(0)).push_back(max_dis_pin.at(i));
                curr_load_remain.at(min_dis_pin.at(0))--;
            } else{
                pin_to_tap.at(min_dis_pin.at(best_tap(min_dis_pin, curr_load_remain))).push_back(max_dis_pin.at(i));
                curr_load_remain.at(min_dis_pin.at(best_tap(min_dis_pin, curr_load_remain)))--;
            }
            if (curr_load_remain.at(min_dis_pin.at(0))==0){
                full_load.push_back(min_dis_pin.at(0));
            }
            min_dis_pin.clear();
        }
        for (int i=0;i<max_dis_pin.size();i++){
            done.push_back(max_dis_pin.at(i));
        }
        /* print the pins assigning step (debug only) */
        /*
        cout<<endl;
        cout<<"max_dis_pin: ";
        for (int i=0;i<max_dis_pin.size();i++){
            cout<<max_dis_pin.at(i)<<" ";
        }
        cout<<endl;
        for (int i=0;i<pin_to_tap.size();i++){
            cout<<"pin_to_tap"<<i<<": ";
            for (int j=0;j<pin_to_tap.at(i).size();j++){
                cout<<pin_to_tap.at(i).at(j)<<" ";    
            }
            cout<<endl;
        }
        for (int i=0;i<curr_load_remain.size();i++){
            cout<<"load_tap"<<i<<": "<<curr_load_remain.at(i)<<endl;
        }
        */
        max_dis_pin.clear();
    }
    /* print the info just from the input file (debug only) */
    /*
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
    */
    for (int i=0;i<pin_to_tap.size();i++){
        out<<"TAP "<<i<<endl;
        out<<"PINS "<<pin_to_tap.at(i).size()<<endl;
        for (int j=0;j<pin_to_tap.at(i).size();j++){
            out<<"PIN "<<pin_to_tap.at(i).at(j)<<endl;
        }
        out<<"ROUTING "<<"x"<<endl;
        for (int j=0;j<5;j++){
            out<<"EDGE "<<"x"<<" "<<"x"<<" "<<"x"<<" "<<"x"<<" "<<endl;
        }
    }
    
    out.close();

    /* measuer time (end) */
    int end = clock();
	std::cout << "it took " << end - start << " ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds." << std::endl;
}
