package pl.ususweb.usus.service;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.Repository.MarketRepository;
import pl.ususweb.usus.entity.Market;

import java.util.List;

@Service
public class MarketService {
    @Autowired
    private MarketRepository marketrepository;

    public List<Market> getmarket(){
        return marketrepository.findAll();
    }
}
