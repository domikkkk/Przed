package pl.ususweb.usus.controler;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import pl.ususweb.usus.service.FinalGradeSettingsService;

@Controller
@RequestMapping("finalGrade")
public class FinalGradeResponseController {

    @Autowired
    private FinalGradeSettingsService finalGradeSettingsService;
    @GetMapping("/edit") public String edit(Model model)
    {
        model.addAttribute("finalGrade", finalGradeSettingsService.getFinalGradeSettings());
        return "edit_final_grade";
    }

}
