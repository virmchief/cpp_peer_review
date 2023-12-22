#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
public:
    Domain(const string& adress) 
        : domain_(adress) {
        reverse(domain_.begin(), domain_.end());
        domain_ += '.';
    }
    
    bool operator==(const Domain& other) const {
        return domain_ == other.domain_;
    }
    
    bool IsSubdomain(const Domain& other) const {
        return other.domain_.substr(0, domain_.size()) == domain_;
    }
    
    string GetDomain() const {
        return domain_;
    }
        
private:
    string domain_;
};

class DomainChecker {
public:
    template <typename Iterator>
    DomainChecker(Iterator first, Iterator last) 
        : forbidden_domains_(first, last) {
        sort(forbidden_domains_.begin(), forbidden_domains_.end(), [](const Domain& lhs, const Domain& rhs) {
            return lhs.GetDomain() < rhs.GetDomain();
        });
        auto last_unique = unique(forbidden_domains_.begin(), forbidden_domains_.end(), [](const Domain& lhs, const Domain& rhs) {
            return lhs.IsSubdomain(rhs);
        });
        forbidden_domains_.erase(last_unique, forbidden_domains_.end());
    }

    bool IsForbidden(const Domain& domain) const {      
        auto it = upper_bound(forbidden_domains_.begin(), forbidden_domains_.end(), domain,
            [](const Domain& forbidden_domain, const Domain& test_domain) {
            return forbidden_domain.GetDomain() < test_domain.GetDomain();
        });
        if(it == forbidden_domains_.begin()) {
            return false;
        }
        return (prev(it) -> IsSubdomain(domain));
    }
    
    void Print() {
        for(const auto& domain : forbidden_domains_) {
            cout << domain.GetDomain() << endl;
        }
    }
    
private:
    vector<Domain> forbidden_domains_;
};

template <typename Number>
vector<Domain> ReadDomains(istream& input, Number num) {
    vector<Domain> result;
    result.reserve(num);
    for(size_t i = 0; i < num; ++i) {
        string domain_name;
        getline(input, domain_name);
        result.push_back({domain_name});
    }
    return result;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());
    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}