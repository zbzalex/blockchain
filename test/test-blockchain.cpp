#include <blockchain/Wallet.hpp>
#include <iostream>
#include <vector>
#include <openssl/bn.h>
#include <cstring>
#include <openssl/sha.h>
#include <blockchain/SHA256.hpp>
#include <blockchain/Tx.hpp>
#include <blockchain/Chain.hpp>
#include <thread>
#include <blockchain/Block.hpp>

int main(int argc, char *argv[])
{
  Wallet wallet;
  // wallet.create();
  wallet.createFromHex("16260783E40B16731673622AC8A5B045FC3EA4AF70F727F3F9E92BDD3A1DDC42");

  std::cout << "priv key " << wallet.getHexKey()
            << "\n"
            << "publ key " << wallet.getHexPubKey()
            << "\n";

  const char message[] = "test";

  uint8_t dig[32];
  ::crypto::SHA256(dig, message, strlen(message));

  uint8_t *sig;
  int siglen;

  wallet.sign(&sig, &siglen, message, strlen(message));

  // const char messageToVerify[] = "test";

  // ::crypto::SHA256(dig, messageToVerify, strlen(messageToVerify));

  // if (wallet.verify(dig, sig, siglen))
  // {
  //   std::cout << "verification successful\n ";
  // }

  Tx *tx = new Tx(
      "0482006E9398A6986EDA61FE91674C3A108C399475BF1E738F19DFC2DB11DB1D28130C6B3B28AEF9A9C7E7143DAC6CF12C09B8444DB61679ABB1D86F85C038A58C",
      "0482006E9398A6986EDA61FE91674C3A108C399475BF1E738F19DFC2DB11DB1D28130C6B3B28AEF9A9C7E7143DAC6CF12C09B8444DB61679ABB1D86F85C038A58C",
      1
  );

  Chain chain;

  chain.addToPending(tx);
  // chain.addToPending(tx);
  
  Block *block = new Block((const char *) "");
  
  chain.addBlock(block);


  Tx *tx2 = new Tx(
      "0482006E9398A6986EDA61FE91674C3A108C399475BF1E738F19DFC2DB11DB1D28130C6B3B28AEF9A9C7E7143DAC6CF12C09B8444DB61679ABB1D86F85C038A58C",
      "0482006E9398A6986EDA61FE91674C3A108C399475BF1E738F19DFC2DB11DB1D28130C6B3B28AEF9A9C7E7143DAC6CF12C09B8444DB61679ABB1D86F85C038A58C",
      100
  );

  chain.addToPending(tx2);

  Block *block2 = chain.newBlock();
  chain.addBlock(block2);

  // std::vector<Tx* > pendingTransactions = chain.getPendingTransactions();
  // decltype(pendingTransactions)::iterator it = pendingTransactions.begin();
  // for( ; it != pendingTransactions.end(); ++it) {
  //   std::cout << "txhash " << (*it)->getHash() << "\n";
  // }


  std::vector<Block *> blocks = chain.getBlocks();
  decltype(blocks)::iterator it = blocks.begin();

  for ( ; it != blocks.end(); ++it ) {
    std::cout << "block index " << (*it)->getIndex() << "\n";
    std::cout << "block prev hash  " << (*it)->getPrevHash()  << "\n";
    std::cout << "block hash  " << (*it)->getHash()  << "\n";
    std::vector<Tx*> transactions = (*it)->getTransactions();
    decltype(transactions)::iterator it2 = transactions.begin();
    for( ; it2 != transactions.end(); ++it2 ) {
      std::cout << "\ttx index " << (*it2)->getIndex() << "\n";
      std::cout << "\ttx hash  " << (*it2)->getHash()  << "\n";
    }

    std::cout << "\n";
  }
}