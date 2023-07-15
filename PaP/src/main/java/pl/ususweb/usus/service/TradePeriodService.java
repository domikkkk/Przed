package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.Repository.TradePeriodRepository;
import pl.ususweb.usus.entity.TradePeriod;

import java.util.List;

@Service
public class TradePeriodService {
    @Autowired
    private TradePeriodRepository tradePeriodRepository;

    public void saveTradePeriod(TradePeriod period) {
        tradePeriodRepository.save(period);
    }

    public TradePeriod getTradePeriod(int id) {
        return tradePeriodRepository.findById(id).orElse(null);
    }

    public List<TradePeriod> getTradePeriods() {
        return tradePeriodRepository.findAll();
    }

    public void removeTradePeriod(int id) {
        tradePeriodRepository.deleteById(id);
    }
}
