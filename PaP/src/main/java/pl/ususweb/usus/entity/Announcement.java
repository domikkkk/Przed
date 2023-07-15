package pl.ususweb.usus.entity;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.time.LocalDateTime;

@Entity
@Getter
@Setter
public class Announcement implements Comparable<Announcement> {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    Integer id;

    String author;

    String headline;
    String info;
    LocalDateTime published;

    @Override
    public int compareTo(Announcement announcement) {
        return getPublished().compareTo(announcement.getPublished());
    }
}
