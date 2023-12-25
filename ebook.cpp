#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Ebook {
public:
    Ebook() 
        : id_page(MAX_ID, 0), users_on_page(MAX_PAGE, 0) {
    }
    
    void ReadAndAnswer(istream& is, ostream& os) {
        int requests_count;
        is >> requests_count;
        for (int i = 0; i < requests_count; ++i) {
            ReadLineAndAnswer(is, os);
        }
    }

private:
    static const int MAX_ID = 1e+5;
    static const int MAX_PAGE = 1e+3;
    
    vector<int> id_page; // the last pages for each user id
    vector<int> users_on_page; // total amount of users id, whitch at last on this page
    
    double AnswerFor_CHEER(const int user_id) {        
        if (id_page[user_id] != 0) {
            if(users_on_page[0] == 1) { // if there is only one user
                return 1;
            }
            int page_of_user = id_page[user_id];
            double fraction = ((users_on_page[0] - users_on_page[page_of_user - 1]) * 1.0) / ((users_on_page[0] - 1) * 1.0);
            return fraction;
        }
        return 0;
    }
    
    void AnswerFor_READ(const int user_id, const int user_page) {
        int user_start = id_page[user_id];
        id_page[user_id] = user_page;
        for(int i = user_start; i < user_page; ++i) {
            ++users_on_page[i];
        }
    }
    
    void ReadLineAndAnswer(istream& is, ostream& os) {
        string request;
        is >> request;
        
        int user_id;
        is >> user_id;
        
        if (request == "CHEER"s) {
            os << setprecision(6) << AnswerFor_CHEER(user_id) << endl;;
        } else if (request == "READ"s) {
            int user_page;
            is >> user_page;
            AnswerFor_READ(user_id, user_page);
        } else {
            throw invalid_argument("Invalid request: "s + request);
        }
    }
};

int main() {
    Ebook ebook;
    ebook.ReadAndAnswer(cin, cout);
    
    return 0;
}