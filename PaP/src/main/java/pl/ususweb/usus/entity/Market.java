package pl.ususweb.usus.entity;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.*;
import java.util.List;

@Entity
@Data
@Table(name = "Market")
public class Market {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @OneToMany
    List<ExchangeOffer> exchangeOfferList;

    //TODO add connection between market and users (students)
}
