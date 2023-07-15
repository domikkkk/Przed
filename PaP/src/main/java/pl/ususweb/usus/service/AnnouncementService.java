package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.Repository.AnnouncementRepository;
import pl.ususweb.usus.entity.Announcement;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

@Service
public class AnnouncementService {
    @Autowired
    private AnnouncementRepository announcementRepository;
    public void saveAnnouncement(Announcement announcement){
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime date = LocalDateTime.now();
        announcement.setPublished(date);
        announcementRepository.save(announcement);
    }

    public Announcement getAnnouncement(int id){
        return announcementRepository.findById(id).orElse(null);
    }

    public List<Announcement> getAnnouncements(){
        return announcementRepository.findAll();
    }

    public void removeAnnouncement(int id){
        announcementRepository.deleteById(id);
    }
}
