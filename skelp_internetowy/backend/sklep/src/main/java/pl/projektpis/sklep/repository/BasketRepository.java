package pl.projektpis.sklep.repository;

import org.springframework.data.cassandra.repository.CassandraRepository;
import org.springframework.stereotype.Repository;
import pl.projektpis.sklep.entity.Basket;
import pl.projektpis.sklep.entity.Product;

import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Repository
public interface BasketRepository extends CassandraRepository<Basket, UUID> {

    public Optional<Basket> findOneByOwner(String user);
    public LinkedList<Basket> findAll(); //for testing
}
