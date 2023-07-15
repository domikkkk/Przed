package pl.ususweb.usus.controler;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.service.ExchangeOfferService;
import pl.ususweb.usus.service.GroupService;
import pl.ususweb.usus.service.StudentService;

import java.security.Principal;

@Controller
@AllArgsConstructor
public class ExchangeOfferResponseController {
    StudentService sService;
    GroupService groupService;
    ExchangeOfferService offerService;


    @Autowired
    StudentService studentService;

    @GetMapping("/exchangeOffer/new") public String get(Model model, Principal p)
    {
        model.addAttribute("students", sService.getStudents());
        model.addAttribute("myGroups", groupService.getTradeableGroupsForStudent(studentService.getStudentByUsername(p.getName())));
        model.addAttribute("availableGroups", groupService.getTradeableGroups());
        return "add_exchange_offer";
    }

    @GetMapping("/exchangeOffer/list") public String get_all(Model model, Principal p)
    {
        Student current = studentService.getStudentByUsername(p.getName());
        model.addAttribute("offers", offerService.getValidExchangeOffersForStudent(current));
        model.addAttribute("myOffers", offerService.getExchangeOffersOwnedBy(current));
        model.addAttribute("kto", current); // kto się wymienia. W drugim kontrolerze kto wystawia.
        return "all_offers";
    }
}
