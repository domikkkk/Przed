package pl.ususweb.usus.controler.REST;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.ExchangeOffer;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.service.ExchangeOfferService;
import pl.ususweb.usus.service.StudentService;

import java.security.Principal;

@RestController // This means that this class is a Controller
@RequestMapping("exchangeOffer")
public class ExchangeOfferController {
    @Autowired
    public ExchangeOfferService exchangeOfferService;
    @Autowired
    public StudentService studentService;
    @PostMapping(path = "/add", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE})
    public @ResponseBody RedirectView addNewExchangeOffer (@ModelAttribute ExchangeOffer period, Principal p) {

        period.setStudent(studentService.getStudentByUsername(p.getName()));
        exchangeOfferService.saveExchangeOffer(period);
        return new RedirectView("/exchangeOffer/list");
    }

    @GetMapping(path = "/change/offerid={id}-sid={sid}-gr={gr}")
    public RedirectView view(@PathVariable("id") Integer id, @PathVariable("sid") Integer sid, @PathVariable("gr") Integer gr){
        ExchangeOffer offer = exchangeOfferService.getExchangeOffer(id);
        Group group = offer.getOfferedGroup(), desiredgroup = null;

        int idx1 = offer.getStudent().getIndeks();
        for (int i=0;i<offer.getDesiredGroups().size();i++){
            Group g = offer.getDesiredGroups().get(i);
            if(g.getId().equals(gr)) {
                desiredgroup = g;
                break;
            }
        }
//        desiredgroup = offer.getDesiredGroups().get(0); // ulepszyć link żeby przekazywał konkretną grupę a nie zawsze pierwszą
        int idx = sid; // index tego co się zamienia, czyli klika "zamień"

        Student student1 = studentService.getStudent(idx1); // ten który oferuje
        Student student2 = studentService.getStudent(idx); // ten co się zamienia
        studentService.removeGroup(student2, desiredgroup); // tutaj może być błąd asercji
        studentService.removeGroup(student1, group);
        student1.getStudentGroups().add(desiredgroup);
        student2.getStudentGroups().add(group);
        exchangeOfferService.removeExchangeOffer(id);
        return new RedirectView("/exchangeOffer/list");
    }

    @GetMapping("/all")
    public @ResponseBody Iterable<ExchangeOffer> getAllExchangeOffers() {

        return exchangeOfferService.getExchangeOffers();
    }

    @GetMapping("/get/{id}")
    public @ResponseBody ExchangeOffer exchangeOffer(@PathVariable("id") int id){
        return exchangeOfferService.getExchangeOffer(id);
    }

    @GetMapping("/delete/{id}")
    public  RedirectView removeExchangeOffer (@PathVariable("id") int id){
        return  exchangeOfferService.removeExchangeOffer(id);
    }
}


