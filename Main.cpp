//Include header files as required
#include <iostream>
#include <string>

using namespace std;
//===============================================================
class PartyMember{
  int member_id; //a unique ID assigned to each member by the political party
  string name; //name of the member
  long asset_value; //net asset of the member
    string nominated_for;  //name of the constituency if this member is nominated by his party for running election 
    //You are not allowed to add any other member variable in this class

  public:    
    //Write a default constructor for this class. Initialize data members as deem appropriate.
        PartyMember(){
            member_id = 0;
            name = "";
            asset_value = 0;
            nominated_for = "";
        }
        
    //Write other parameterize constructors as required.
        PartyMember(string n, long asset){
            member_id = 0;
            name = n;
            asset_value = asset;
            nominated_for = "";
        }
        
    //Write the setter functions for this class
        void set_member_id(int id){
            member_id = id;
        }
        
        void set_name(string n){
            name = n;
        }
        
        void set_asset_value(long asset){
            asset_value = asset;
        }
        
        void set_nominated_for(string constituency){
            nominated_for = constituency;
        }
        
        //Write the getter functions for this class
        int get_member_id(){
            return member_id;
        }
        
        string get_name(){
            return name;
        }
        
        long get_asset_value(){
            return asset_value;
        }
        
        string get_nominated_for(){
            return nominated_for;
        }
            
    void show_member_details(){
            //Print member details in the format shown in the given sample output
            cout << "ID: " << member_id << ", Name: " << name << ", Asset: " << asset_value;
            if(nominated_for != ""){
                cout << ", Constituency: " << nominated_for;
            }
            cout << endl;
    }
        //Add any other helper functions as required    
};
//===============================================================
class PoliticalParty{
  string name; //name of the political party
  PartyMember* members[1000]; //Array of pointers to PartyMember objects; Allocate an object to a pointer when a member is added. Assume that there will be at most 1000 members in a party
  int member_count; //count of members in the party
    
    //Add other member variables as required and justified
    int next_id; //To track the next ID to assign (IDs are never reused)

  public:    
    //Write a copy constructor for this class
        PoliticalParty(const PoliticalParty& pp){
            name = pp.name;
            member_count = pp.member_count;
            next_id = pp.next_id;
            for(int i = 0; i < member_count; i++){
                members[i] = new PartyMember(*(pp.members[i]));
            }
        }

        //Write other parameterize constructors as required
        PoliticalParty(string party_name){
            name = party_name;
            member_count = 0;
            next_id = 1;
            for(int i = 0; i < 1000; i++){
                members[i] = nullptr;
            }
        }

    //Write a destructor for this class
        ~PoliticalParty(){
            for(int i = 0; i < member_count; i++){
                delete members[i];
            }
        }

        //Write setter functions for this class
        void set_name(string party_name){
            name = party_name;
        }

        //Write getter functions for this class
        string get_name(){
            return name;
        }
        
        int get_member_count(){
            return member_count;
        }
                
        PartyMember search_member(string constituency){
            //Returns the member nominated for the given constituency. If not found, return an empty object.
            for(int i = 0; i < member_count; i++){
                if(members[i]->get_nominated_for() == constituency){
                    return *(members[i]);
                }
            }
            return PartyMember();
        }

        void join_party(PartyMember m){    
            //Add the member m to this party. Assign id sequentially to the new member.
            members[member_count] = new PartyMember(m);
            members[member_count]->set_member_id(next_id);
            next_id++;
            member_count++;
    }

    void join_party(PoliticalParty& pp){
            //Add all the members of pp to this party and remove them from pp. Assign ids sequentially to the new members in this party. When a member joins from one party to another, his nomination, if given, from the old party is automatically cancelled.
            for(int i = 0; i < pp.member_count; i++){
                members[member_count] = new PartyMember(*(pp.members[i]));
                members[member_count]->set_member_id(next_id);
                members[member_count]->set_nominated_for(""); //Cancel nomination
                next_id++;
                member_count++;
            }
            //Remove all members from pp
            for(int i = 0; i < pp.member_count; i++){
                delete pp.members[i];
                pp.members[i] = nullptr;
            }
            pp.member_count = 0;
    }

        void leave_party(int id){
            //Remove the member with the given id from this party. Rearrange the list such that all the members are consecutive, i.e., there is no hole in the list. When a member leaves a party, his id is never reused.
            int index = -1;
            for(int i = 0; i < member_count; i++){
                if(members[i]->get_member_id() == id){
                    index = i;
                    break;
                }
            }
            
            if(index != -1){
                delete members[index];
                //Shift all members after this index to the left
                for(int i = index; i < member_count - 1; i++){
                    members[i] = members[i + 1];
                }
                members[member_count - 1] = nullptr;
                member_count--;
            }
    }
    
        void nominate_member(int id, string constituency){
            //Nominate the member with given id for the constituency
            for(int i = 0; i < member_count; i++){
                if(members[i]->get_member_id() == id){
                    members[i]->set_nominated_for(constituency);
                    break;
                }
            }
        }

        void show_nominated_members(){
            //Show details of the members nominated for the election. Match the format as given in the expected output.
            cout << endl << "Nominated Members of " << name << ":" << endl;
            for(int i = 0; i < member_count; i++){
                if(members[i]->get_nominated_for() != ""){
                    members[i]->show_member_details();
                }
            }
    }

        void cancel_nomination(int id){    
            //Cancel nomination of the member with the given id
            for(int i = 0; i < member_count; i++){
                if(members[i]->get_member_id() == id){
                    members[i]->set_nominated_for("");
                    break;
                }
            }
    }

        PoliticalParty form_new_party(string name){  
            //Form a new party with the members who have been denied nomination from this party
            PoliticalParty new_party(name);
            
            //Find members who were nominated but now are not
            int i = 0;
            while(i < member_count){
                if(members[i]->get_nominated_for() == ""){
                    //Check if this member was previously nominated (had nomination cancelled)
                    //Add to new party
                    new_party.members[new_party.member_count] = new PartyMember(*(members[i]));
                    new_party.members[new_party.member_count]->set_member_id(new_party.next_id);
                    new_party.next_id++;
                    new_party.member_count++;
                    
                    //Remove from current party
                    delete members[i];
                    for(int j = i; j < member_count - 1; j++){
                        members[j] = members[j + 1];
                    }
                    members[member_count - 1] = nullptr;
                    member_count--;
                }
                else{
                    i++;
                }
            }
            
            return new_party;
    }

        void show_all_members(){
            //Print details info of all the members of this party in the format shown in the given expected output
            cout << endl << "Members of " << name << ":" << endl;
            if(member_count == 0){
                cout << "No members found." << endl;
            }
            else{
                for(int i = 0; i < member_count; i++){
                    members[i]->show_member_details();
                }
            }
    }

        //Add any other helper function as required and justified
};
//=======================================
int main(){
    PartyMember abc1("Mr. A", 100000000);
    PartyMember abc2("Mr. B", 4000000);
    PartyMember abc3("Mr. C",20000000);
  PoliticalParty p1("ABC");
  p1.join_party(abc1);
  p1.join_party(abc2);
    p1.join_party(abc3);
  p1.show_all_members();

    p1.nominate_member(1,"DHK-10");
    PartyMember pm=p1.search_member("DHK-10");
    cout<<endl<<"Details of the member nominated for DHK-10 constituency:"<<endl;
    pm.show_member_details();

    p1.nominate_member(2,"CUM-3");
    p1.nominate_member(3,"SYL-1");
    p1.show_nominated_members();

    PartyMember xyz1("Mr. X", 1000000);
  PartyMember xyz2("Mr. Y", 3000000);
      
    PoliticalParty p2("XYZ"); 
    p2.join_party(xyz1);
  p2.join_party(xyz2);
    p2.show_all_members();
    
    p1.join_party(p2);
    p1.show_all_members();
    p2.show_all_members();
    
    PartyMember xyz3("Mr. Z",5000000);
    p2.join_party(xyz3);
    p2.show_all_members();
  
    p1.cancel_nomination(1);
    p1.cancel_nomination(3);
    p1.nominate_member(4,"CUM-3");
    p1.nominate_member(5,"SYL-1");
    p1.show_nominated_members();    
    
    PoliticalParty p3=p1.form_new_party("Renegades");
    p1.show_all_members();
    p3.show_all_members();    
}

/* Expected Output
Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000
ID: 2, Name: Mr. B, Asset: 4000000
ID: 3, Name: Mr. C, Asset: 20000000

Details of the member nominated for DHK-10 constituency:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10

Nominated Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 3, Name: Mr. C, Asset: 20000000, Constituency: SYL-1

Members of XYZ:
ID: 1, Name: Mr. X, Asset: 1000000
ID: 2, Name: Mr. Y, Asset: 3000000

Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 3, Name: Mr. C, Asset: 20000000, Constituency: SYL-1
ID: 4, Name: Mr. X, Asset: 1000000
ID: 5, Name: Mr. Y, Asset: 3000000

Members of XYZ:
No members found.

Members of XYZ:
ID: 3, Name: Mr. Z, Asset: 5000000

Nominated Members of ABC:
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 4, Name: Mr. X, Asset: 1000000, Constituency: CUM-3
ID: 5, Name: Mr. Y, Asset: 3000000, Constituency: SYL-1

Members of ABC:
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 4, Name: Mr. X, Asset: 1000000, Constituency: CUM-3
ID: 5, Name: Mr. Y, Asset: 3000000, Constituency: SYL-1

Members of Renegades:
ID: 1, Name: Mr. A, Asset: 100000000
ID: 2, Name: Mr. C, Asset: 20000000
*/
