//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.8.0; //Exercise 1
contract Factory {  
  uint idDigits = 16; //Exercise 2
  uint idModulus = 10 ** idDigits; //Exercise 3
//Exercise 4
  struct Product {
      string name;
      uint id;

  }
  //Exercise 5
   Product[] public products;
   //Exercise 6
   /*function _createProduct(string memory _name, uint _id) 
   private {
      products.push(Product(_name, _id));
   }*/

//Exercise 7&8
   function _generateRandomId(string memory _str) private view
    returns (uint) {
        uint rand = uint (keccak256(abi.encodePacked(_str)));
       return (rand%idModulus);
          
   }
   function _createRandomProduct(string memory _name, uint _age) public
   {
      uint randId = _generateRandomId(_name);
       _createProduct(_name, randId);
       age[randId] = _age;
       validationUsers(randId); 

   }
//Exercise 9
   event NewProduct(uint ArrayProductId, string name, uint id );
    function _createProduct(string memory _name, uint _id) 
   private {
     //uint ArrayProductid = products.push(Product(_name,_id))-1;
     //array.push(NewProduct(_ArrayProductid,_name)) ;
     products.push(Product(_name,_id));
     uint ArrayProductId = (products.length- 1);
     emit NewProduct(ArrayProductId,_name,_id);
   }
//Exercise 10
     mapping(uint => address) public productToOwner;
     mapping(address => uint) OwnerProductCount;

//Exercise 11
    function Ownership (uint ArrayProductId) public {
    productToOwner[ArrayProductId] = msg.sender ;
    OwnerProductCount[msg.sender]++; 
   }
//Exercise 12
  function getProductsByOwner (address _owner) external view 
   returns(uint[] memory) {
     uint counter = 0;
     uint array = OwnerProductCount[_owner];
    uint[] memory result = new uint[] (array);
    for (uint i = 0; i< products.length; i++) {
       if (productToOwner[i]== _owner){
         result[counter]= i;
         counter++;
       }
    }
     return result;

   }
   ////Exercise 13 done
   
   //Exercise 14
   function validationUsers( uint _userId) private view olderThan(18,_userId) {

    }
    mapping (uint => uint) private age;  

    modifier olderThan (uint _age, uint _userId) {

        require (age[_userId] >= _age, "UNDERAGE");

        _;
    }
    
}

