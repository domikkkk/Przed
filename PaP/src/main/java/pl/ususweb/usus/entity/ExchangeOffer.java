package pl.ususweb.usus.entity;

import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.util.List;

@Entity
@Data
@NoArgsConstructor
public class ExchangeOffer {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    Integer id;

    String info;

    @ManyToOne
    Student student;

    @ManyToOne
    Group offeredGroup;

    @ManyToMany
    @JoinTable(
            name = "desired_groups",
            joinColumns = @JoinColumn(name = "exchange_offer.id"),
            inverseJoinColumns = @JoinColumn(name = "group.id"))
    List<Group> desiredGroups;
}
