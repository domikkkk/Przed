package pl.ususweb.usus.entity;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.time.LocalDate;

@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class GradedTest {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    Integer Id;

    String Title;

    // Which activity this test is associated with
    @ManyToOne
    @JoinColumn(name = "activity_id")
    Activity activity;

    Float maxPoints; // minimum is 0

    LocalDate testDate;


}
