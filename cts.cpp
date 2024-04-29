#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cstdlib>
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
vector<int> return_vector_int4(int a, int b, int c, int d){
    vector<int> temp_vector_int;
    temp_vector_int.push_back(a);
    temp_vector_int.push_back(b);
    temp_vector_int.push_back(c);
    temp_vector_int.push_back(d);
    return temp_vector_int;
}
/* check if the vector contain required element */
bool vec_contain(vector<int> vec, int target){
    for (int i=0;i<vec.size();i++){
        if (vec.at(i)==target){
            return true;
        }
    }
    return false;
}
/* in grouping part, check which tap has max load remain */
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
/* calculate the manhattan distance of 2 point */
int manhattan_distance(int x1, int y1, int x2, int y2){
    return (abs(x1-x2)+abs(y1-y2));
}
/* check if a point lie on a line */
bool lie_on_line(int point_x, int point_y, int line_start_x, int line_start_y, int line_end_x, int line_end_y){
    if (line_start_x==line_end_x){ /* vertical line */
        if (point_x==line_start_x){
            if (std::min(line_start_y,line_end_y)<=point_y||point_y<=max(line_start_y,line_end_y)){
                return true;
            }
        }
    } else{ /* horizontal line */
        if (point_y==line_start_y){
            if (std::min(line_start_x,line_end_x)<=point_x||point_x<=max(line_start_x,line_end_x)){
                return true;
            }
        }
    }
    return false;
}
/* check if the edge overlap the existing edges */
vector<vector <int> > overlap(vector<vector<int> > line_list, vector<int> line_test){
    vector<vector<int> > potential_line_list;
    vector<vector<int> > overlap_list;
    if (line_test.at(0)==line_test.at(2)){ /* vertical line */
        for (int i=0;i<line_list.size();i++){
            if (line_list.at(i).at(0)==line_list.at(i).at(2)&&line_list.at(i).at(2)==line_test.at(2)){
                potential_line_list.push_back(line_list.at(i));
            }
        }
        for (int i=0;i<potential_line_list.size();i++){
            vector<int> list;
            vector<int> test;
            vector<bool> list_found(2,false);
            vector<bool> test_found(2,false);
            list.push_back(potential_line_list.at(i).at(1));
            list.push_back(potential_line_list.at(i).at(3));
            test.push_back(line_test.at(1));
            test.push_back(line_test.at(3));
            /* sort the list and test */
            if (list.at(0)>list.at(1)){
                int temp=list.at(0);
                list.at(0)=list.at(1);
                list.at(1)=temp;
            }
            if (test.at(0)>test.at(1)){
                int temp=test.at(0);
                test.at(0)=test.at(1);
                test.at(1)=temp;
            }

            int list_index=0, test_index=0;
            while (list_index<2&&test_index<2){
                if (list.at(list_index)<=test.at(test_index)){
                    list_found.at(list_index)=true;
                    list_index++;
                } else{
                    test_found.at(test_index)=true;
                    test_index++;
                }
            }
            if (list_index==2){
                if (test_index==1){
                    if (std::max(test.at(0),list.at(0))!=list.at(1)){
                        overlap_list.push_back(return_vector_int4(line_test.at(0),std::max(test.at(0),list.at(0)),line_test.at(2),list.at(1)));
                    }
                }
            } else if (test_index==2){
                if (list_index==1){
                    if (std::max(test.at(0),list.at(0))!=test.at(1)){
                        overlap_list.push_back(return_vector_int4(line_test.at(0),std::max(test.at(0),list.at(0)),line_test.at(2),test.at(1)));
                    }
                }
            }
        }
    } else{ /* horizontal line */
        for (int i=0;i<line_list.size();i++){
            if (line_list.at(i).at(1)==line_list.at(i).at(3)&&line_list.at(i).at(3)==line_test.at(3)){
                potential_line_list.push_back(line_list.at(i));
            }
        }
        for (int i=0;i<potential_line_list.size();i++){
            vector<int> list;
            vector<int> test;
            vector<bool> list_found(2,false);
            vector<bool> test_found(2,false);
            list.push_back(potential_line_list.at(i).at(0));
            list.push_back(potential_line_list.at(i).at(2));
            test.push_back(line_test.at(0));
            test.push_back(line_test.at(2));
            /* sort the list and test */
            if (list.at(0)>list.at(1)){
                int temp=list.at(0);
                list.at(0)=list.at(1);
                list.at(1)=temp;
            }
            if (test.at(0)>test.at(1)){
                int temp=test.at(0);
                test.at(0)=test.at(1);
                test.at(1)=temp;
            }

            int list_index=0, test_index=0;
            while (list_index<2&&test_index<2){
                if (list.at(list_index)<=test.at(test_index)){
                    list_found.at(list_index)=true;
                    list_index++;
                } else{
                    test_found.at(test_index)=true;
                    test_index++;
                }
            }
            if (list_index==2){
                if (test_index==1){
                    if (std::max(test.at(0),list.at(0))!=list.at(1)){
                        overlap_list.push_back(return_vector_int4(std::max(test.at(0),list.at(0)),line_test.at(1),list.at(1),line_test.at(3)));    
                    }
                    
                }
            } else if (test_index==2){
                if (list_index==1){
                    if (std::max(test.at(0),list.at(0))!=test.at(1)){
                        overlap_list.push_back(return_vector_int4(std::max(test.at(0),list.at(0)),line_test.at(1),test.at(1),line_test.at(3)));
                    }
                    
                }
            }
        }
    }
    return overlap_list;
}
void set_overlap(vector<vector<int> > line_list, vector<int> line_test, vector<vector<vector<int> > > &capacity_list, int capacity_level){
    if (capacity_list.size()<=capacity_level){
        return;
    }
    set_overlap(capacity_list.at(capacity_level),line_test,capacity_list,capacity_level+1);
    vector<vector<int> > overlap_list;
    overlap_list=overlap(line_list,line_test);
    for (int k=0;k<overlap_list.size();k++){
        capacity_list.at(capacity_level).push_back(overlap_list.at(k));
    }
    
}
void step(vector<vector<int> > &grid, int start_x, int start_y, int end_x, int end_y, int no_step, int grid_size, vector<vector<vector<int> > > capacity_list, vector<vector<int> > &next_expend, bool &found){
    if (start_x==end_x&&start_y==end_y){
        found=true;
        return;
    }
    vector <int> point;
    if (start_x>=0&&start_x<grid_size&&start_y+1>=0&&start_y+1<grid_size&&grid.at(start_y+1).at(start_x)==0){
        if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x,start_y+1)).size()==0){
            grid.at(start_y+1).at(start_x)=no_step;
            point.push_back(start_x);
            point.push_back(start_y+1);
            next_expend.push_back(point);
            point.clear(); 
        }
            
    }
    if (start_x>=0&&start_x<grid_size&&start_y-1>=0&&start_y-1<grid_size&&grid.at(start_y-1).at(start_x)==0){
        if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x,start_y-1)).size()==0){
            grid.at(start_y-1).at(start_x)=no_step;
            point.push_back(start_x);
            point.push_back(start_y-1);
            next_expend.push_back(point);
            point.clear();
        }
    }
    if (start_x+1>=0&&start_x+1<grid_size&&start_y>=0&&start_y<grid_size&&grid.at(start_y).at(start_x+1)==0){
        if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x+1,start_y)).size()==0){
            grid.at(start_y).at(start_x+1)=no_step;
            point.push_back(start_x+1);
            point.push_back(start_y);
            next_expend.push_back(point);
            point.clear();
        }
    }
    if (start_x-1>=0&&start_x-1<grid_size&&start_y>=0&&start_y<grid_size&&grid.at(start_y).at(start_x-1)==0){
        if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x-1,start_y)).size()==0){
            grid.at(start_y).at(start_x-1)=no_step;
            point.push_back(start_x-1);
            point.push_back(start_y);
            next_expend.push_back(point);
            point.clear();
        }
    }
}
bool path_finding(int start_x, int start_y, int end_x, int end_y, int &previous_line_added, int &previous_point_added, vector<int> &cur_x, vector<int> &cur_y, vector<vector<vector<int> > > &capacity_list, int grid_size){
    /* setup the array */
    vector<int> grid_sub(grid_size,0);
    vector<vector<int> > grid(grid_size,grid_sub);
    /* set starting point to special number avoid being traversed */
    int starting_point_code=-2;
    grid.at(start_y).at(start_x)=starting_point_code;
    /*
    for (int i=grid.size()-1;i>=0;i--){
        for (int j=0;j<grid.at(i).size();j++){
            cout<<setw(3)<<grid.at(i).at(j);
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    */
    vector<int> point;
    vector<vector<int> > being_expend;
    vector<vector<int> > next_expend;
    bool found=false;
    point.push_back(start_x);
    point.push_back(start_y);
    being_expend.push_back(point);
    point.clear();
    int no_step=1;
    while (!found&&being_expend.size()>0){
        step(grid,being_expend.at(0).at(0),being_expend.at(0).at(1),end_x,end_y,no_step,grid_size,capacity_list,next_expend,found);
        being_expend.erase(being_expend.begin());
        if (being_expend.size()==0){
            /*
            for (int i=grid.size()-1;i>=0;i--){
                for (int j=0;j<grid.at(i).size();j++){
                    cout<<setw(3)<<grid.at(i).at(j);
                }
                cout<<endl;
            }
            cout<<endl<<endl;
            */
            being_expend=next_expend;
            no_step++;
        }
    }
    vector<vector<int> >found_edge;
    if (found){
        previous_point_added=0;
        int cx=end_x;
        int cy=end_y;
        cur_x.push_back(cx);
        cur_y.push_back(cy);
        previous_point_added++;
        while (cx!=start_x||cy!=start_y){
            if (((cx>=0&&cx<grid_size&&cy+1>=0&&cy+1<grid_size&&grid.at(cy).at(cx)-grid.at(cy+1).at(cx)==1)||(cy+1==start_y&&cx==start_x))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx,cy+1)).size()==0){
                found_edge.push_back(return_vector_int4(cx,cy,cx,cy+1));
                cy++;
            } else if (((cx>=0&&cx<grid_size&&cy-1>=0&&cy-1<grid_size&&grid.at(cy).at(cx)-grid.at(cy-1).at(cx)==1)||(cy-1==start_y&&cx==start_x))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx,cy-1)).size()==0){
                found_edge.push_back(return_vector_int4(cx,cy,cx,cy-1));
                cy--;
            } else if (((cx+1>=0&&cx+1<grid_size&&cy>=0&&cy<grid_size&&grid.at(cy).at(cx)-grid.at(cy).at(cx+1)==1)||(cy==start_y&&cx+1==start_x))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx+1,cy)).size()==0){
                found_edge.push_back(return_vector_int4(cx,cy,cx+1,cy));
                cx++;
            } else if (((cx-1>=0&&cx-1<grid_size&&cy>=0&&cy<grid_size&&grid.at(cy).at(cx)-grid.at(cy).at(cx-1)==1)||(cy==start_y&&cx-1==start_x))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx-1,cy)).size()==0){
                found_edge.push_back(return_vector_int4(cx,cy,cx-1,cy));
                cx--;
            }
            cur_x.push_back(cx);
            cur_y.push_back(cy);
            set_overlap(capacity_list.at(0),found_edge.at(found_edge.size()-1),capacity_list,1);
            capacity_list.at(0).push_back(found_edge.at(found_edge.size()-1));
            previous_point_added++;
        }
        previous_line_added=1;
    }
    /*
    for (int i=0;i<found_edge.size();i++){
        for (int j=0;j<found_edge.at(i).size();j++){
            cout<<found_edge.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
    */
    return found;
}
int main(int argc, char * argv[]){
    /* measure time (start) */
    int start = clock();

    /* command input validation */
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

    /* read the input file */
    string info_type;
    ifstream in(inFile);    //input filestream
    ofstream out(outFile);  //output filestream
    int max_runtime, max_load, grid_size, capacity, temp_num, temp_x, temp_y, num_pins, num_taps;
    vector<pin *> pins;
    vector<tap *> taps;
    
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
    vector<vector<int> > pin_to_tap_route=pin_to_tap;
    vector<vector<vector<int> > > capacity_list(capacity);
    vector<int> line_cutoff(1,0);
    //i=tap
    //j=pin_to
    //k=point_from
    for (int i=0;i<taps.size();i++){
        int previous_line_added=0;
        int previous_point_added=0;
        //cout<<"tap"<<i<<endl;
        vector<int> cur_x;
        vector<int> cur_y;
        cur_x.push_back(taps.at(i)->x);
        cur_y.push_back(taps.at(i)->y);
        while (pin_to_tap_route.at(i).size()>0){
            /*
            cout<<"cur_x: ";
            for (int j=0;j<cur_x.size();j++){
                cout<<cur_x.at(j)<<" ";
            }
            cout<<endl;
            cout<<"cur_y: ";
            for (int j=0;j<cur_y.size();j++){
                cout<<cur_y.at(j)<<" ";
            }
            cout<<endl;
            */
            int min=99999999;
            int from_x=-1;
            int from_y=-1;
            int to_x=-1;
            int to_y=-1;
            int to_index=0;
            for (int j=0;j<pin_to_tap_route.at(i).size();j++){
                for (int k=0;k<cur_x.size();k++){
                    //cout<<manhattan_distance(cur_x.at(k),cur_y.at(k),pins.at(pin_to_tap_route.at(i).at(j))->x,pins.at(pin_to_tap_route.at(i).at(j))->y)<<" ";
                    if(manhattan_distance(cur_x.at(k),cur_y.at(k),pins.at(pin_to_tap_route.at(i).at(j))->x,pins.at(pin_to_tap_route.at(i).at(j))->y)<min){
                        min=manhattan_distance(cur_x.at(k),cur_y.at(k),pins.at(pin_to_tap_route.at(i).at(j))->x,pins.at(pin_to_tap_route.at(i).at(j))->y);
                        from_x=cur_x.at(k);
                        from_y=cur_y.at(k);
                        to_x=pins.at(pin_to_tap_route.at(i).at(j))->x;
                        to_y=pins.at(pin_to_tap_route.at(i).at(j))->y;
                        to_index=j;
                    }
                }
            }
            //cout<<endl;
            pin_to_tap_route.at(i).erase(pin_to_tap_route.at(i).begin()+to_index);
            /* print the from and to*/
            /*
            cout<<"from_x: "<<from_x<<endl;
            cout<<"from_y: "<<from_y<<endl;
            cout<<"to_x: "<<to_x<<endl;
            cout<<"to_y: "<<to_y<<endl;
            */
            /* remove the line and point */
            if (capacity_list.at(0).size()>0&&previous_line_added>1){
                if (lie_on_line(from_x,from_y,capacity_list.at(0).at(capacity_list.at(0).size()-1).at(0),capacity_list.at(0).at(capacity_list.at(0).size()-1).at(1),capacity_list.at(0).at(capacity_list.at(0).size()-1).at(2),capacity_list.at(0).at(capacity_list.at(0).size()-1).at(3)) || lie_on_line(from_x,from_y,capacity_list.at(0).at(capacity_list.at(0).size()-2).at(0),capacity_list.at(0).at(capacity_list.at(0).size()-2).at(1),capacity_list.at(0).at(capacity_list.at(0).size()-2).at(2),capacity_list.at(0).at(capacity_list.at(0).size()-2).at(3))){
                    /* remove line */
                    for (int k=0;k<2;k++){
                        capacity_list.at(0).erase(capacity_list.at(0).end()-3);
                    }
                    /* remove point */
                    for (int k=0;k<previous_point_added/2;k++){
                        cur_x.erase(cur_x.end()-1-previous_point_added/2);
                        cur_y.erase(cur_y.end()-1-previous_point_added/2);
                    }
                    
                } else{
                    /* remove line */
                    for (int k=0;k<2;k++){
                        capacity_list.at(0).erase(capacity_list.at(0).end()-1);
                    }
                    /* remove point*/
                    for (int k=0;k<previous_point_added/2;k++){
                        cur_x.erase(cur_x.end()-1);
                        cur_y.erase(cur_y.end()-1);
                    }
                    
                }
            }

            /* add the line */
            bool ignore_capacity=false;
            if (from_x==to_x){  /* vertical line */
                if((overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,to_x,to_y)).size()==0)||ignore_capacity){
                    set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,to_x,to_y),capacity_list,1);
                    capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,to_x,to_y));
                    for (int k=std::min(from_y,to_y);k<=std::max(from_y,to_y);k++){
                        cur_x.push_back(from_x);
                        cur_y.push_back(k);
                    }
                    previous_line_added=1;
                    previous_point_added=abs(from_y-to_y)+1;
                } else{
                    /* path finding */
                    bool path_exist=false;
                    vector<int>not_routable_x;
                    vector<int>not_routable_y;
                    // int fail=0;
                    while (not_routable_x.size()<cur_x.size()){
                        path_exist=path_finding(from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size);
                        if (!path_exist){
                            // fail++;
                            // cout<<fail<<endl;
                            not_routable_x.push_back(from_x);
                            not_routable_y.push_back(from_y);
                            int re_min=99999999;
                            int re_from_x=-1;
                            int re_from_y=-1;
                            bool fail_point=false;
                            for (int k=0;k<cur_x.size();k++){
                                for (int l=0;l<not_routable_x.size();l++){
                                    if (cur_x.at(k)==not_routable_x.at(l)&&cur_y.at(k)==not_routable_y.at(l)){
                                        fail_point=true;
                                        break;
                                    }
                                }
                                if (fail_point){
                                    continue;
                                }
                                if(manhattan_distance(cur_x.at(k),cur_y.at(k),to_x,to_y)<re_min){
                                    re_min=manhattan_distance(cur_x.at(k),cur_y.at(k),to_x,to_y);
                                    re_from_x=cur_x.at(k);
                                    re_from_y=cur_y.at(k);
                                }
                            }

                            from_x=re_from_x;
                            from_y=re_from_y;
                        } else{
                            break;
                        }
                    }
                    /* path finding not work */
                    if (!path_exist){
                        cout<<"exceed capacity vertical"<<endl;
                        cout<<from_x<<" "<<from_y<<" "<<to_x<<" "<<to_y<<endl;
                        set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,to_x,to_y),capacity_list,1);
                        capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,to_x,to_y));
                        for (int k=std::min(from_y,to_y);k<=std::max(from_y,to_y);k++){
                            cur_x.push_back(from_x);
                            cur_y.push_back(k);
                        }
                        previous_line_added=1;
                        previous_point_added=abs(from_y-to_y)+1;
                    }
                }
            } else if (from_y==to_y){   /* horizontal line */
                if((overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,to_x,to_y)).size()==0)||ignore_capacity){
                    set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,to_x,to_y),capacity_list,1);
                    capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,to_x,to_y));
                    for (int k=std::min(from_x,to_x);k<=std::max(from_x,to_x);k++){
                        cur_x.push_back(k);
                        cur_y.push_back(from_y);
                    }
                    previous_line_added=1;
                    previous_point_added=abs(from_y-to_y)+1;
                } else{
                    /* path finding */
                    bool path_exist=false;
                    vector<int>not_routable_x;
                    vector<int>not_routable_y;
                    // int fail=0;
                    while (not_routable_x.size()<cur_x.size()){
                        path_exist=path_finding(from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size);
                        if (!path_exist){
                            // fail++;
                            // cout<<fail<<endl;
                            not_routable_x.push_back(from_x);
                            not_routable_y.push_back(from_y);
                            int re_min=99999999;
                            int re_from_x=-1;
                            int re_from_y=-1;
                            bool fail_point=false;
                            for (int k=0;k<cur_x.size();k++){
                                for (int l=0;l<not_routable_x.size();l++){
                                    if (cur_x.at(k)==not_routable_x.at(l)&&cur_y.at(k)==not_routable_y.at(l)){
                                        fail_point=true;
                                        break;
                                    }
                                }
                                if (fail_point){
                                    continue;
                                }
                                if(manhattan_distance(cur_x.at(k),cur_y.at(k),to_x,to_y)<re_min){
                                    re_min=manhattan_distance(cur_x.at(k),cur_y.at(k),to_x,to_y);
                                    re_from_x=cur_x.at(k);
                                    re_from_y=cur_y.at(k);
                                }
                            }

                            from_x=re_from_x;
                            from_y=re_from_y;
                        } else{
                            break;
                        }
                    }
                    /* path finding not work */
                    if (!path_exist){
                        cout<<"exceed capacity horizontal"<<endl;
                        cout<<from_x<<" "<<from_y<<" "<<to_x<<" "<<to_y<<endl;
                        set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,to_x,to_y),capacity_list,1);
                        capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,to_x,to_y));
                        for (int k=std::min(from_x,to_x);k<=std::max(from_x,to_x);k++){
                            cur_x.push_back(k);
                            cur_y.push_back(from_y);
                        }
                        previous_line_added=1;
                        previous_point_added=abs(from_y-to_y)+1;
                    }
                }

            } else{
                /* first l shape */
                bool first_lshape=true;
                previous_line_added=0;
                if((overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,to_x,from_y)).size()==0)&&(overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(to_x,from_y,to_x,to_y)).size()==0)||ignore_capacity){
                    set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,to_x,from_y),capacity_list,1);
                    set_overlap(capacity_list.at(0),return_vector_int4(to_x,from_y,to_x,to_y),capacity_list,1);
                    capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,to_x,from_y));
                    for (int k=std::min(from_x,to_x);k<=std::max(from_x,to_x);k++){
                        cur_x.push_back(k);
                        cur_y.push_back(from_y);
                    }
                    capacity_list.at(0).push_back(return_vector_int4(to_x,from_y,to_x,to_y));
                    for (int k=std::min(from_y,to_y);k<=std::max(from_y,to_y);k++){
                        cur_x.push_back(to_x);
                        cur_y.push_back(k);
                    }
                    previous_line_added++;
                    first_lshape=true;    
                } else{
                    first_lshape=false;
                }
                /* second l shape*/
                bool need_path_finding=false;
                if((overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,from_x,to_y)).size()==0)&&(overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,to_x,to_y)).size()==0)||ignore_capacity){
                    set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,from_x,to_y),capacity_list,1);
                    set_overlap(capacity_list.at(0),return_vector_int4(from_x,to_y,to_x,to_y),capacity_list,1);
                    capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,from_x,to_y));
                    for (int k=std::min(from_y,to_y);k<=std::max(from_y,to_y);k++){
                        cur_x.push_back(from_x);
                        cur_y.push_back(k);
                    }
                    capacity_list.at(0).push_back(return_vector_int4(from_x,to_y,to_x,to_y));
                    for (int k=std::min(from_x,to_x);k<=std::max(from_x,to_x);k++){
                        cur_x.push_back(k);
                        cur_y.push_back(to_y);
                    }
                    previous_line_added++;
                } else{
                    need_path_finding=true;
                }
                if (!first_lshape&&need_path_finding){
                    /* path finding */
                    bool path_exist=false;
                    vector<int>not_routable_x;
                    vector<int>not_routable_y;
                    // int fail=0;
                    while (not_routable_x.size()<cur_x.size()){
                        path_exist=path_finding(from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size);
                        if (!path_exist){
                            // fail++;
                            // cout<<fail<<endl;
                            not_routable_x.push_back(from_x);
                            not_routable_y.push_back(from_y);
                            int re_min=99999999;
                            int re_from_x=-1;
                            int re_from_y=-1;
                            bool fail_point=false;
                            for (int k=0;k<cur_x.size();k++){
                                for (int l=0;l<not_routable_x.size();l++){
                                    if (cur_x.at(k)==not_routable_x.at(l)&&cur_y.at(k)==not_routable_y.at(l)){
                                        fail_point=true;
                                        break;
                                    }
                                }
                                if (fail_point){
                                    continue;
                                }
                                if(manhattan_distance(cur_x.at(k),cur_y.at(k),to_x,to_y)<re_min){
                                    re_min=manhattan_distance(cur_x.at(k),cur_y.at(k),to_x,to_y);
                                    re_from_x=cur_x.at(k);
                                    re_from_y=cur_y.at(k);
                                }
                            }

                            from_x=re_from_x;
                            from_y=re_from_y;
                        } else{
                            break;
                        }
                    }/* path finding not work */
                    if (!path_exist){
                        cout<<"exceed capacity L shape"<<endl;
                        cout<<from_x<<" "<<from_y<<" "<<to_x<<" "<<to_y<<endl;
                        set_overlap(capacity_list.at(0),return_vector_int4(from_x,from_y,from_x,to_y),capacity_list,1);
                        set_overlap(capacity_list.at(0),return_vector_int4(from_x,to_y,to_x,to_y),capacity_list,1);
                        capacity_list.at(0).push_back(return_vector_int4(from_x,from_y,from_x,to_y));
                        for (int k=std::min(from_y,to_y);k<=std::max(from_y,to_y);k++){
                            cur_x.push_back(from_x);
                            cur_y.push_back(k);
                        }
                        capacity_list.at(0).push_back(return_vector_int4(from_x,to_y,to_x,to_y));
                        for (int k=std::min(from_x,to_x);k<=std::max(from_x,to_x);k++){
                            cur_x.push_back(k);
                            cur_y.push_back(to_y);
                        }
                        previous_line_added++;
                    }

                }
                if (!need_path_finding||first_lshape){
                    previous_point_added=previous_line_added*(abs(from_y-to_y)+1+abs(from_x-to_x)+1);
                }
                
            }
            

            /* remove line 1 more time for last routing step */
            if (capacity_list.at(0).size()>0&&previous_line_added>1&&pin_to_tap_route.at(i).size()==0){
                capacity_list.at(0).erase(capacity_list.at(0).end()-1);
                capacity_list.at(0).erase(capacity_list.at(0).end()-1);
            }
            /* print the line added*/
            /*
            cout<<"line: "<<endl;
            for (int j=0;j<capacity_list.at(0).size();j++){
                for (int k=0;k<capacity_list.at(0).at(j).size();k++){
                    cout<<capacity_list.at(0).at(j).at(k)<<" ";
                }
                cout<<endl;
            }
            */
            
            
        }
        line_cutoff.push_back(capacity_list.at(0).size());
        //cout<<endl;
    }
    /*
    vector<vector<int> > overlap_list=overlap(capacity_list.at(0),{2,6,4,6});
    cout<<"overlap2: "<<(overlap(capacity_list.at(0),{4,8,6,8}).size()==0&&overlap(capacity_list.at(0),{6,8,6,6}).size()==0)<<endl;
    cout<<"overlap: "<<endl;
    for (int i=0;i<overlap_list.size();i++){
        for (int j=0;j<overlap_list.at(i).size();j++){
            cout<<overlap_list.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
    */
    /* print the capacity list */
    /*
    for (int i=0;i<capacity_list.size();i++){
        cout<<"capacity_level "<<i<<": "<<endl;
        for (int j=0;j<capacity_list.at(i).size();j++){
            for (int k=0;k<capacity_list.at(i).at(j).size();k++){
                cout<<capacity_list.at(i).at(j).at(k)<<" ";
            }
            cout<<endl;
        }
    }
    */
    // vector<int> cur_x;
    // vector<int> cur_y;
    // int previous_point_added=0, previous_line_added=0;
    // path_finding(7,6,6,9,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size);
    /* output file */
    for (int i=0;i<pin_to_tap.size();i++){
        out<<"TAP "<<i<<endl;
        out<<"PINS "<<pin_to_tap.at(i).size()<<endl;
        for (int j=0;j<pin_to_tap.at(i).size();j++){
            out<<"PIN "<<pin_to_tap.at(i).at(j)<<endl;
        }
        out<<"ROUTING "<<line_cutoff.at(i+1)-line_cutoff.at(i)<<endl;
        for (int j=line_cutoff.at(i);j<line_cutoff.at(i+1);j++){
            out<<"EDGE "<<capacity_list.at(0).at(j).at(0)<<" "<<capacity_list.at(0).at(j).at(1)<<" "<<capacity_list.at(0).at(j).at(2)<<" "<<capacity_list.at(0).at(j).at(3)<<" "<<endl;
        }
    }
    
    out.close();
    

    /* measuer time (end) */
    int end = clock();
	std::cout << "it took " << end - start << " ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds." << std::endl;
}
