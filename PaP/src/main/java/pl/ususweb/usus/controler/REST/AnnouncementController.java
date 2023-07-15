package pl.ususweb.usus.controler.REST;

import lombok.AllArgsConstructor;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.Announcement;
import pl.ususweb.usus.service.AnnouncementService;

import java.util.Collections;
import java.util.List;

@RestController
@AllArgsConstructor
@RequestMapping("announcement")
public class AnnouncementController {
    private AnnouncementService announcementService;
    @PostMapping(path = "/add", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE})
    public RedirectView addAnnouncement(@ModelAttribute Announcement announcement) {
        announcementService.saveAnnouncement(announcement);
        return new RedirectView("/dashboard");
    }
    @GetMapping("/all")
    public @ResponseBody Iterable<Announcement> getAllAnnouncements() {

        List<Announcement> all =  announcementService.getAnnouncements();
        Collections.reverse(all);
        return all;
    }

    @GetMapping("/get/{id}")
    public @ResponseBody Announcement announcement(@PathVariable("id") Integer id){
        return announcementService.getAnnouncement(id);
    }

    @GetMapping("/delete/{id}")
    public RedirectView removeAnnouncement(@PathVariable("id") int id){
        announcementService.removeAnnouncement(id);
        return new RedirectView("/dashboard");
    }
}
