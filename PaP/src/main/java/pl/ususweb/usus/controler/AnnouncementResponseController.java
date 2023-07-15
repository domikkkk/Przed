package pl.ususweb.usus.controler;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import pl.ususweb.usus.service.AnnouncementService;

import java.security.Principal;

@Controller
@AllArgsConstructor
public class AnnouncementResponseController {
    @Autowired
    private AnnouncementService announcementService;
    @GetMapping("/announcement/new") public String get(Model model, Principal p)
    {
        model.addAttribute("author",p.getName());
        return "add_announcement";
    }
}
