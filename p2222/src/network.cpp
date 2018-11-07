#include "network.h"
#include "random.h"
#include <iostream>

using namespace std;

void Network::resize(const size_t& a){
	values.resize(a);
	RandomNumbers RNG(0);
	RNG.uniform_double(values, 0, values.size());
}

bool Network::add_link(const size_t& a, const size_t& b){
	if(a!=b and a<size() and b<size() and a>=0 and b>=0){
		for(auto element : neighbors(a)){
			if(element==b){
				return false;
			}
		}
		links.insert({a,b});
		links.insert({b,a});	
		return true;
	}else{
		return false;
	}
}

size_t Network::random_connect(const double& mean_deg){
		for(auto it = links.begin(); it != links.end(); ){
		it = links.erase(it);
    }
	vector<int> nb_links (values.size());
	RandomNumbers RN(0);
	RN.poisson(nb_links, mean_deg);
	size_t nb(0);
	bool added_(false);
	for (int i(0); i<nb_links.size() ; ++i){
		for (int j(1); j<=nb_links[i]; ++j){
			while (not(added_)){
				added_ = add_link(values[i], RNG.uniform_double(0,values.size()-1));
			}
			++ nb;
		}
	}
	return nb;
}
	
size_t Network::set_values(const vector<double>& vec){
	links.clear();
	values.clear();
	resize(vec.size());
	for(size_t i(0); i<vec.size(); ++i){
		values[i]=vec[i];
	}
	return values.size();
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t & _n) const{
	if(_n > links.size()){
		return links.count(_n);  
	} else {
		return 0;
	}							
}

double Network::value(const size_t & _n) const{
	if(_n < values.size()){
		return values[_n];  
	} else {
		return 0;
	}							 
}

vector<double> Network::sorted_values() const{
	vector<double> sorted(values);
	sort(sorted.begin(), sorted.end(), greater<double>());
	return sorted;
}

vector<size_t> Network::neighbors(const size_t& a) const{
	vector<size_t> link_a;
	for (auto elements : links){
		if(elements.first == a ){
			link_a.push_back(elements.second);
		}
	}
	return link_a;
}

