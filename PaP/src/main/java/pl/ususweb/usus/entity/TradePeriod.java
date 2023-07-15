package pl.ususweb.usus.entity;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.time.LocalDate;

@Entity
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class TradePeriod {

        @javax.persistence.Id
        @GeneratedValue(strategy = GenerationType.AUTO)
        Integer Id;

        @ManyToOne
        @JoinColumn(name = "activity_id")
        Activity activity;

        LocalDate startDate;

        LocalDate endDate;
}
