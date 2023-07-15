package pl.ususweb.usus.service;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.Repository.ExchangeOfferRepository;
import pl.ususweb.usus.entity.ExchangeOffer;
import pl.ususweb.usus.entity.Student;

import java.util.ArrayList;
import java.util.List;

@Service
@AllArgsConstructor
public class ExchangeOfferService {
    @Autowired
    private ExchangeOfferRepository exchangeOfferRepository;
    public void saveExchangeOffer(ExchangeOffer exchangeOffer){
        exchangeOfferRepository.save(exchangeOffer);
    }

    public ExchangeOffer getExchangeOffer(Integer id){
        return exchangeOfferRepository.findById(id).orElse(null);
    }

    public List<ExchangeOffer> getExchangeOffers(){
        return exchangeOfferRepository.findAll();
    }

    public RedirectView removeExchangeOffer(Integer id){
        exchangeOfferRepository.deleteById(id);
        return new RedirectView("/exchangeOffer/list");
    }

    public List<ExchangeOffer> getValidExchangeOffersForStudent(Student current) {

        List<ExchangeOffer> offers = exchangeOfferRepository.findAll();
        List<ExchangeOffer> invalid = new ArrayList<>();

        for (ExchangeOffer offer : offers){
            if (offer.getDesiredGroups().stream().noneMatch(current.getStudentGroups()::contains)){
                invalid.add(offer);
            }
        }
        offers.removeAll(invalid);
        offers.removeAll(getExchangeOffersOwnedBy(current));
        return offers;


    }

    public List<ExchangeOffer> getExchangeOffersOwnedBy(Student current) {
        List<ExchangeOffer> owned = new ArrayList<>();
        for (ExchangeOffer offer : exchangeOfferRepository.findAll()){
            if (offer.getStudent()==current){
                owned.add(offer);
            }
        }
        return owned;
    }
}
