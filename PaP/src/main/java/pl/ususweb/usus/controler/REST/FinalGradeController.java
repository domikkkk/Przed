package pl.ususweb.usus.controler.REST;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.FinalGradeSettings;
import pl.ususweb.usus.service.FinalGradeSettingsService;

@RestController
@RequestMapping("/finalGrade")
public class FinalGradeController {

    @Autowired
    FinalGradeSettingsService finalGradeSettingsService;

    @PostMapping("/update")
    public RedirectView updateFinalGrade (FinalGradeSettings settings){

        finalGradeSettingsService.saveSettings(settings);

        return new RedirectView("/dashboard");
    }

}
