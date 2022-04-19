//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.8.0;
contract Factory {
  uint idDigits = 16;
  uint idModulus = 10 ** idDigits;

  struct Product {
      string name;
      uint id;

  }
   Product[] public products;
   /*function _createProduct(string memory _name, uint _id) 
   private {
      products.push(Product(_name, _id));
   }*/

   function _generateRandomId(string memory _str) private view
    returns (uint) {
        uint rand = uint (keccak256(abi.encodePacked(_str)));
       return (rand%idModulus);
          
   }
   function _createRandomProduct(string memory _name) public
   {
      uint randID = _generateRandomId(_name);
       _createProduct(_name, randID);

   }

   event NewProduct(uint ProductId, string name, uint id );
    function _createProduct(string memory _name, uint _id) 
   private {
     //uint ArrayProductid = products.push(Product(_name,_id))-1;
     //array.push(NewProduct(_ArrayProductid,_name)) ;
     products.push(Product(_name,_id));
     uint ProductId = (products.length- 1);
     emit NewProduct(ProductId,_name,_id);
   }
     mapping(uint => address) public productToOwner;
   //mapping(address => uint) public productToOwner;
     mapping(address => uint) OwnerProductCount;

    function Ownership () public {
    productToOwner= msg.sender ;
    OwnerProductCount += msg.sender; 
   }
   
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
   
    mapping (uint => uint) public age;
    modifier olderThan (uint _age, uint _userId)
    {
      require( _userId >= _age );
              _;

    }
    function validationUsers( uint _userId) public view olderThan(18,_userId) {

    }

}

