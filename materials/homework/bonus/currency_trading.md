# Currency Trading Simulation in Go

### Program Description

The program simulates currency trading activities in a fictional market using concurrency. It focuses on three currency pairs: EUR/USD, GBP/USD, and JPY/USD.

#### simulateMarketData Function

The `simulateMarketData` function simulates the price fluctuation of currency pairs and sends simulated data over channels at regular intervals:

- **EUR/USD Price Simulation**: Generates random prices between 1.0 and 1.5.
- **GBP/USD Price Simulation**: Generates random prices between 1.0 and 1.5.
- **JPY/USD Price Simulation**: Generates random prices between 0.006 and 0.009.

These prices are generated every second and sent through respective channels (`EUR/USD`, `GBP/USD`, `JPY/USD`).

#### selectPair Function

The `selectPair` function utilizes Go's `select` statement to manage buy and sell operations based on predefined conditions:

- **EUR/USD Sell Condition**: If the EUR/USD price exceeds 1.20, it initiates a sell operation. This operation is simulated with a delay of 4 seconds before confirmation.
- **GBP/USD Buy Condition**: If the GBP/USD price falls below 1.35, it initiates a buy operation. This operation is simulated with a delay of 3 seconds before confirmation.
- **JPY/USD Buy Condition**: If the JPY/USD price falls below 0.0085, it initiates a buy operation. This operation is simulated with a delay of 3 seconds before confirmation.

#### Program Execution

- The program runs for one minute (`time.Sleep(1 * time.Minute)`) to simulate a trading session.
- Goroutines are used for concurrent execution of `simulateMarketData` and `selectPair` functions.
- Synchronization is handled using `sync.WaitGroup` to ensure proper termination of goroutines.

### Conclusion

The program effectively demonstrates how to use Go's concurrency features (goroutines and channels) to simulate currency trading activities in a fictional market. It leverages `select` for non-blocking channel operations and simulates trading delays to mimic real-world trading behaviors. At the end of the one-minute simulation period, the program gracefully terminates.






