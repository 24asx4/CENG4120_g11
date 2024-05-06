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
vector<int> return_vector_int2(int a, int b){
    vector<int> temp_vector_int;
    temp_vector_int.push_back(a);
    temp_vector_int.push_back(b);
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
/* set overlap list */
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
/* set the min distance between point and pin, then clear the point list */
void reset_point(vector <int> &cur_x, vector <int> &cur_y, vector <vector<int> > pin_to_tap_route, vector <vector<int> > &pin_shortest_point, int i, vector<pin *>  pins){
    
    for (int j=0;j<pin_to_tap_route.at(i).size();j++){
        int min_by_pin=99999999;
        int from_x_by_pin=-1;
        int from_y_by_pin=-1;
        int to_x_by_pin=-1;
        int to_y_by_pin=-1;
        int to_index_by_pin=0;
        for (int k=0;k<cur_x.size();k++){
            if(manhattan_distance(cur_x.at(k),cur_y.at(k),pins.at(pin_to_tap_route.at(i).at(j))->x,pins.at(pin_to_tap_route.at(i).at(j))->y)<min_by_pin){
                min_by_pin=manhattan_distance(cur_x.at(k),cur_y.at(k),pins.at(pin_to_tap_route.at(i).at(j))->x,pins.at(pin_to_tap_route.at(i).at(j))->y);
                from_x_by_pin=cur_x.at(k);
                from_y_by_pin=cur_y.at(k);
                to_x_by_pin=pins.at(pin_to_tap_route.at(i).at(j))->x;
                to_y_by_pin=pins.at(pin_to_tap_route.at(i).at(j))->y;
                to_index_by_pin=j;
            }
        }
        if (min_by_pin<manhattan_distance(pin_shortest_point.at(j).at(0),pin_shortest_point.at(j).at(1),pin_shortest_point.at(j).at(2),pin_shortest_point.at(j).at(3))){
            pin_shortest_point.at(j).at(0)=from_x_by_pin;
            pin_shortest_point.at(j).at(1)=from_y_by_pin;
            pin_shortest_point.at(j).at(2)=to_x_by_pin;
            pin_shortest_point.at(j).at(3)=to_y_by_pin;
        }
        
        
    }

    cur_x.clear();
    cur_y.clear();
    
}

/* in path finding, expand the neighborhood if there is a edge that doesn't exceed capacity */
void step(vector<vector<int> > &grid, int start_x, int start_y, int end_x, int end_y, int grid_size, vector<vector<vector<int> > > capacity_list, vector<vector<int> > &next_expend, bool &found, bool add_detour){
    if (start_x==end_x&&start_y==end_y){
        found=true;
        return;
    }
    int no_step;
    if (grid.at(start_y).at(start_x)==-2){
        no_step=1;
    } else{
        no_step=grid.at(start_y).at(start_x)+1;
    }
    if (start_x>=0&&start_x<grid_size&&start_y+1>=0&&start_y+1<grid_size&&grid.at(start_y+1).at(start_x)==-10&&!found){
        if (add_detour||manhattan_distance(start_x,start_y+1,end_x,end_y)<manhattan_distance(start_x,start_y,end_x,end_y)){
            if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x,start_y+1)).size()==0){
                grid.at(start_y+1).at(start_x)=no_step;
                next_expend.push_back(return_vector_int2(start_x,start_y+1));
            }
        }   
    }
    if (start_x>=0&&start_x<grid_size&&start_y-1>=0&&start_y-1<grid_size&&grid.at(start_y-1).at(start_x)==-10&&!found){
        if (add_detour||manhattan_distance(start_x,start_y-1,end_x,end_y)<manhattan_distance(start_x,start_y,end_x,end_y)){
            if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x,start_y-1)).size()==0){
                grid.at(start_y-1).at(start_x)=no_step;
                next_expend.push_back(return_vector_int2(start_x,start_y-1));
            }
        }
    }
    if (start_x+1>=0&&start_x+1<grid_size&&start_y>=0&&start_y<grid_size&&grid.at(start_y).at(start_x+1)==-10&&!found){
        if (add_detour||manhattan_distance(start_x+1,start_y,end_x,end_y)<manhattan_distance(start_x,start_y,end_x,end_y)){
            if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x+1,start_y)).size()==0){
                grid.at(start_y).at(start_x+1)=no_step;
                next_expend.push_back(return_vector_int2(start_x+1,start_y));
            }
        }
    }
    if (start_x-1>=0&&start_x-1<grid_size&&start_y>=0&&start_y<grid_size&&grid.at(start_y).at(start_x-1)==-10&&!found){
        if (add_detour||manhattan_distance(start_x-1,start_y,end_x,end_y)<manhattan_distance(start_x,start_y,end_x,end_y)){
            if (overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(start_x,start_y,start_x-1,start_y)).size()==0){
                grid.at(start_y).at(start_x-1)=no_step;
                next_expend.push_back(return_vector_int2(start_x-1,start_y));
            }
        }
    }
}
/* path finding, hadlock's alg. */
bool path_finding(int start_x, int start_y, int end_x, int end_y, int &previous_line_added, int &previous_point_added, vector<int> &cur_x, vector<int> &cur_y, vector<vector<vector<int> > > &capacity_list, int grid_size, vector <vector<int> > pin_to_tap_route, vector <vector<int> > &pin_shortest_point, int i, vector<pin *>  pins){    
    /* setup the array */
    vector<int> grid_sub(grid_size,-10);
    vector<vector<int> > grid(grid_size,grid_sub);
    /* set starting point to special number avoid being traversed */
    int starting_point_code=-2;
    grid.at(start_y).at(start_x)=starting_point_code;
    vector<vector<int> > being_expend;
    vector<vector<int> > next_expend;
    vector<vector<int> > corner;
    bool found=false;
    being_expend.push_back(return_vector_int2(start_x,start_y));
    corner.push_back(return_vector_int2(start_x,start_y));
    int no_step=1;
    bool cur_detour_done=false;
    /* expand */
    while (!found&&being_expend.size()>0){
        for (int i=0;i<being_expend.size();i++){
            step(grid,being_expend.at(i).at(0),being_expend.at(i).at(1),end_x,end_y,grid_size,capacity_list,next_expend,found,false);
        }
        int earse_counter=0;
		for (int i=0;i<corner.size();i++){
			if (corner.at(i-earse_counter).at(0)>=0&&corner.at(i-earse_counter).at(0)<grid_size&&corner.at(i-earse_counter).at(1)+1>=0&&corner.at(i-earse_counter).at(1)+1<grid_size&&grid.at(corner.at(i-earse_counter).at(1)+1).at(corner.at(i-earse_counter).at(0))==-10){
				continue;
			}
			if (corner.at(i-earse_counter).at(0)>=0&&corner.at(i-earse_counter).at(0)<grid_size&&corner.at(i-earse_counter).at(1)-1>=0&&corner.at(i-earse_counter).at(1)-1<grid_size&&grid.at(corner.at(i-earse_counter).at(1)-1).at(corner.at(i-earse_counter).at(0))==-10){
				continue;
			}
			if (corner.at(i-earse_counter).at(0)+1>=0&&corner.at(i-earse_counter).at(0)+1<grid_size&&corner.at(i-earse_counter).at(1)>=0&&corner.at(i-earse_counter).at(1)<grid_size&&grid.at(corner.at(i-earse_counter).at(1)).at(corner.at(i-earse_counter).at(0)+1)==-10){
				continue;
			}
			if (corner.at(i-earse_counter).at(0)-1>=0&&corner.at(i-earse_counter).at(0)-1<grid_size&&corner.at(i-earse_counter).at(1)>=0&&corner.at(i-earse_counter).at(1)<grid_size&&grid.at(corner.at(i-earse_counter).at(1)).at(corner.at(i-earse_counter).at(0)-1)==-10){
				continue;
			}
			corner.erase(corner.begin()+i-earse_counter);
			earse_counter++;
		}
        if (next_expend.size()!=0){
            being_expend=next_expend;
            next_expend.clear();
            no_step++;
            cur_detour_done=false;
        } else{
            for (int i=0;i<corner.size();i++){
				step(grid,corner.at(i).at(0),corner.at(i).at(1),end_x,end_y,grid_size,capacity_list,next_expend,found,true);
			}
			if (cur_detour_done){
				break;
			}
			cur_detour_done=true;
        }
    }
    /* backtrace */
    vector<vector<int> >found_edge;
    if (found){
        reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
        cur_x.clear();
        cur_y.clear();
        previous_point_added=0;
        int cx=end_x;
        int cy=end_y;
        cur_x.push_back(cx);
        cur_y.push_back(cy);
        previous_point_added++;
        while (cx!=start_x||cy!=start_y){
            bool edge_added=false;
            if (((cy+1==start_y&&cx==start_x)||(cx>=0&&cx<grid_size&&cy+1>=0&&cy+1<grid_size&&grid.at(cy).at(cx)-grid.at(cy+1).at(cx)==1))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx,cy+1)).size()==0){
                if (found_edge.size()>0&&found_edge.at(found_edge.size()-1).at(2)==cx&&found_edge.at(found_edge.size()-1).at(3)==cy){
                    if (found_edge.at(found_edge.size()-1).at(0)==found_edge.at(found_edge.size()-1).at(2)){
                        found_edge.at(found_edge.size()-1).at(3)=cy+1;
                        edge_added=true;
                    }
                }
                if (!edge_added){
                    found_edge.push_back(return_vector_int4(cx,cy,cx,cy+1));
                }
                cy++;
            } else if (((cy-1==start_y&&cx==start_x)||(cx>=0&&cx<grid_size&&cy-1>=0&&cy-1<grid_size&&grid.at(cy).at(cx)-grid.at(cy-1).at(cx)==1))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx,cy-1)).size()==0){
                if (found_edge.size()>0&&found_edge.at(found_edge.size()-1).at(2)==cx&&found_edge.at(found_edge.size()-1).at(3)==cy){
                    if (found_edge.at(found_edge.size()-1).at(0)==found_edge.at(found_edge.size()-1).at(2)){
                        found_edge.at(found_edge.size()-1).at(3)=cy-1;
                        edge_added=true;
                    }
                }
                if (!edge_added){
                    found_edge.push_back(return_vector_int4(cx,cy,cx,cy-1));
                }
                cy--;
            } else if (((cy==start_y&&cx+1==start_x)||(cx+1>=0&&cx+1<grid_size&&cy>=0&&cy<grid_size&&grid.at(cy).at(cx)-grid.at(cy).at(cx+1)==1))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx+1,cy)).size()==0){
                if (found_edge.size()>0&&found_edge.at(found_edge.size()-1).at(2)==cx&&found_edge.at(found_edge.size()-1).at(3)==cy){
                    if (found_edge.at(found_edge.size()-1).at(1)==found_edge.at(found_edge.size()-1).at(3)){
                        found_edge.at(found_edge.size()-1).at(2)=cx+1;
                        edge_added=true;
                    }
                }
                if (!edge_added){
                    found_edge.push_back(return_vector_int4(cx,cy,cx+1,cy));
                }
                cx++;
            } else if (((cy==start_y&&cx-1==start_x)||(cx-1>=0&&cx-1<grid_size&&cy>=0&&cy<grid_size&&grid.at(cy).at(cx)-grid.at(cy).at(cx-1)==1))&&overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(cx,cy,cx-1,cy)).size()==0){
                if (found_edge.size()>0&&found_edge.at(found_edge.size()-1).at(2)==cx&&found_edge.at(found_edge.size()-1).at(3)==cy){
                    if (found_edge.at(found_edge.size()-1).at(1)==found_edge.at(found_edge.size()-1).at(3)){
                        found_edge.at(found_edge.size()-1).at(2)=cx-1;
                        edge_added=true;
                    }
                }
                if (!edge_added){
                    found_edge.push_back(return_vector_int4(cx,cy,cx-1,cy));
                }
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
    return found;
}
/* find a new point to route to the pin */
void new_point_for_path_finding(bool &path_exist, int from_x, int from_y, int to_x, int to_y, int &previous_line_added, int &previous_point_added, vector<int> &cur_x, vector<int> &cur_y, vector<vector<vector<int> > > &capacity_list, int grid_size, vector <vector<int> > pin_to_tap_route, vector <vector<int> > &pin_shortest_point, int i, vector<pin *>  pins){
    vector<int>not_routable_x;
    vector<int>not_routable_y;
    // int fail=0;
    while (not_routable_x.size()<cur_x.size()){
        
        path_exist=path_finding(from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size,pin_to_tap_route, pin_shortest_point, i, pins);
        if (!path_exist){
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
            if (re_from_x==-1||re_from_y==-1){
                break;
            }
            from_x=re_from_x;
            from_y=re_from_y;
        } else{
            // cout<<"fail: "<<fail<<" success finally"<<endl;
            break;
        }
        // cout<<"fail: "<<fail<<endl;
        // fail++;
    }
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
        } else if (info_type=="END"){
            in>>info_type;
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
    /* run the alg */
    vector<int> max_dis_pin;
    vector<int> min_dis_pin;
    vector<int> done;
    vector<vector <int> > pin_to_tap(num_taps);
    vector<int> full_load;
    vector <vector <int> > max_num_each_pin;
    for (int i=0;i<pin_d.size();i++){
        vector <int> temp_2;
        int max_dis=-1;
        for (int j=0;j<pin_d.at(i).size();j++){
            if (pin_d.at(i).at(j)>max_dis){
                max_dis=pin_d.at(i).at(j);
            }
        }
        temp_2.push_back(max_dis);
        temp_2.push_back(i);
        max_num_each_pin.push_back(temp_2);
        temp_2.clear();
    }
    while (max_num_each_pin.size()>0){
        int max_dis=-1;
        for (int i=0;i<max_num_each_pin.size();i++){
            if (max_num_each_pin.at(i).at(0)>max_dis){
                max_dis_pin.clear();
                done.clear();
                max_dis=max_num_each_pin.at(i).at(0);
                if (!vec_contain(max_dis_pin, max_num_each_pin.at(i).at(1))){
                    max_dis_pin.push_back(max_num_each_pin.at(i).at(1));
                    done.push_back(i);
                }
            } else if (max_num_each_pin.at(i).at(0)==max_dis){
                if (!vec_contain(max_dis_pin, max_num_each_pin.at(i).at(1))){
                    max_dis_pin.push_back(max_num_each_pin.at(i).at(1));
                    done.push_back(i);
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

        for (int i=0;i<done.size();i++){
            max_num_each_pin.erase(max_num_each_pin.begin()+done.at(i)-i);
        }
        max_dis_pin.clear();
    }
    vector<vector<int> > pin_to_tap_route=pin_to_tap;
    vector<vector<vector<int> > > capacity_list(capacity);
    vector<int> line_cutoff(1,0);
    for (int i=0;i<taps.size();i++){
        int previous_line_added=0;
        int previous_point_added=0;
        vector<int> cur_x;
        vector<int> cur_y;
        vector<vector<int> > pin_shortest_point(pin_to_tap_route.at(i).size());
        for (int j=0;j<pin_shortest_point.size();j++){
            pin_shortest_point.at(j).push_back(taps.at(i)->x);
            pin_shortest_point.at(j).push_back(taps.at(i)->y);
            pin_shortest_point.at(j).push_back(pins.at(pin_to_tap_route.at(i).at(j))->x);
            pin_shortest_point.at(j).push_back(pins.at(pin_to_tap_route.at(i).at(j))->y);
        }
        cur_x.push_back(taps.at(i)->x);
        cur_y.push_back(taps.at(i)->y);
        while (pin_to_tap_route.at(i).size()>0){
            int min=99999999;
            int from_x=-1;
            int from_y=-1;
            int to_x=-1;
            int to_y=-1;
            int to_index=0;
            for (int j=0;j<pin_to_tap_route.at(i).size();j++){
                for (int k=0;k<cur_x.size();k++){
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
            int min_by_pin=99999999;
            int min_by_pin_index=0;
            for (int j=0;j<pin_shortest_point.size();j++){
                
                if (min_by_pin>manhattan_distance(pin_shortest_point.at(j).at(0),pin_shortest_point.at(j).at(1),pin_shortest_point.at(j).at(2),pin_shortest_point.at(j).at(3))){
                    min_by_pin=manhattan_distance(pin_shortest_point.at(j).at(0),pin_shortest_point.at(j).at(1),pin_shortest_point.at(j).at(2),pin_shortest_point.at(j).at(3));
                    min_by_pin_index=j;
                }
            }
            if (min>min_by_pin){
                from_x=pin_shortest_point.at(min_by_pin_index).at(0);
                from_y=pin_shortest_point.at(min_by_pin_index).at(1);
                to_x=pin_shortest_point.at(min_by_pin_index).at(2);
                to_y=pin_shortest_point.at(min_by_pin_index).at(3);
                pin_shortest_point.erase(pin_shortest_point.begin()+min_by_pin_index);
                pin_to_tap_route.at(i).erase(pin_to_tap_route.at(i).begin()+min_by_pin_index);
            } else{
                pin_shortest_point.erase(pin_shortest_point.begin()+to_index);
                pin_to_tap_route.at(i).erase(pin_to_tap_route.at(i).begin()+to_index);
            }
            
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

                    reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
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
                    new_point_for_path_finding(path_exist,from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size,pin_to_tap_route,pin_shortest_point,i,pins);
                    /* path finding not work */
                    if (!path_exist){
                        cout<<"exceed capacity vertical"<<endl;
                        cout<<from_x<<" "<<from_y<<" "<<to_x<<" "<<to_y<<endl;
                        reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
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
                    
                    reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
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
                    new_point_for_path_finding(path_exist,from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size,pin_to_tap_route,pin_shortest_point,i,pins);
                    /* path finding not work */
                    if (!path_exist){
                        cout<<"exceed capacity horizontal"<<endl;
                        cout<<from_x<<" "<<from_y<<" "<<to_x<<" "<<to_y<<endl;
                        reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
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
                if(((overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,to_x,from_y)).size()==0)&&(overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(to_x,from_y,to_x,to_y)).size()==0))||ignore_capacity){
                    
                    reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
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
                if(((overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,from_x,to_y)).size()==0)&&(overlap(capacity_list.at(capacity_list.size()-1),return_vector_int4(from_x,from_y,to_x,to_y)).size()==0))||ignore_capacity){
                    
                    
                    if (!first_lshape){

                        reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins); 
                    }
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
                    new_point_for_path_finding(path_exist,from_x,from_y,to_x,to_y,previous_line_added,previous_point_added,cur_x,cur_y,capacity_list,grid_size,pin_to_tap_route,pin_shortest_point,i,pins);
                    /* path finding not work */
                    if (!path_exist){
                        cout<<"exceed capacity L shape"<<endl;
                        cout<<from_x<<" "<<from_y<<" "<<to_x<<" "<<to_y<<endl;
                        reset_point(cur_x, cur_y, pin_to_tap_route, pin_shortest_point, i, pins);
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
        }
        line_cutoff.push_back(capacity_list.at(0).size());
    }
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
	std::cout << "whole it took " << end - start << " ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds." << std::endl;
}
