#include "network.h"
#include "random.h"
#include <algorithm>


size_t Network:: random_connect(const double& mean){
	links.clear();
	size_t links_added(0);
	
	
	for(size_t i(0); i<size(); ++i){
	    int n_nodes(RNG.poisson(mean)); //nombre des nodes auxquels le node i va ètre lié
		std::vector<int>links_to_add(n_nodes, 0); 
	    RNG.uniform_int(links_to_add); //les indices des nodes qu'on va lier sont donnés par un tableau de taille n_nodes auquel on applique la distribution uniforme
	    
	    for(int n(0); n< n_nodes; ++n){
		  if(add_link(i, links_to_add[n])) { ++links_added;}
			
		}
    }
      
	return links_added;  
	
}	
	


void  Network:: resize(const size_t& n){
	
	values.resize(n);
	RNG.normal(values);   
}	



bool Network:: add_link(const size_t& a, const size_t& b){
	

		
	if((a!= b)and(a<size())and(b<size())){	//verifie que les nodes a et b appartiennent au tableau et qu'ils ne sont pas égaux
	
	std::vector<size_t> neighbors_a(neighbors(a));
	std::vector<size_t>::iterator it;
	it = find(neighbors_a.begin(), neighbors_a.end(),b);
	        if(it== neighbors_a.end()){ //ajoute un lien que s'il n'existe pas déja un lien entre le node a et le node b
		
			links.insert(std::pair<size_t,size_t>(a,b));
	        links.insert(std::pair<size_t,size_t>(b,a));
			return true;}
	}
		
	return false;   
	
}


double Network::value(const size_t &_n) const{
	if(_n<values.size()){return values[_n];}
	return false;
}


size_t Network::size() const{
	return values.size();
}



size_t Network::degree(const size_t &_n) const{
	return links.count(_n);
} 


std::vector<size_t> Network::neighbors(const size_t& n) const{
	std::vector<size_t> neighbors;
	 
	 for(auto I: links){
		if(I.first == n){
			neighbors.push_back(I.second);}
		}
	
	return neighbors;
}


size_t Network:: set_values(const std::vector<double>& val){
	values.clear();
	values = val;
	return size();
}
	
	
std::vector<double> Network::sorted_values() const{
    std::vector<double> ordered_values(values);
    std::sort(ordered_values.begin(), ordered_values.end(), std::greater<double>());	
    return ordered_values;
}


