package pl.ususweb.usus.controler;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import pl.ususweb.usus.Repository.StudentRepository;
import pl.ususweb.usus.entity.Activity;
import pl.ususweb.usus.service.TradePeriodService;

import java.security.Principal;
import java.time.LocalDate;

@Controller
@RequestMapping("/tradePeriod")
public class TradePeriodResponseController {

    @Autowired
    TradePeriodService tradePeriodService;

    @Autowired
    StudentRepository studentRepository;;

    @GetMapping("/list")
    public String list(Model model, Principal principal)
    {
        model.addAttribute("tradePeriods",tradePeriodService.getTradePeriods());
        model.addAttribute("currentDate", LocalDate.now());

        if (studentRepository.existsByUsername(principal.getName()))
        {
            return "all_trade_periods_student";
        }
        return "all_trade_periods";
    }

    @GetMapping("/add/{activity}")
    public String add(Model model, @Value("${usus.dateFormat}") String dateFormat, Activity activity)
    {
        model.addAttribute("dateFormat",dateFormat);
        model.addAttribute("activity",activity.getId());


        return "add_trade_period";
    }

}
