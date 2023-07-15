package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.FinalGradeSettings;

public interface FinalGradeSettingsRepository extends JpaRepository<FinalGradeSettings, Integer> {
}
