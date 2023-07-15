package pl.ususweb.usus.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.ususweb.usus.entity.Market;

public interface MarketRepository extends JpaRepository<Market, Integer> {
}
