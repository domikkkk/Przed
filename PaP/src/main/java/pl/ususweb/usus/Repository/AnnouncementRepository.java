package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.Announcement;

public interface AnnouncementRepository extends JpaRepository<Announcement, Integer> {
}
