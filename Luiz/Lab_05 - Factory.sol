//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 < 0.8.0;

// Exercise 1
contract Factory {
   uint idDigits=16; // Exercise 2
   uint idModulus=10**idDigits; // Exercise 3
    
   struct Product { // Exercise 4
       string name;
       uint id;
   }
  
    Product[] public products; //Exercise 5

    /*function _createProduct(string memory _name, uint _id) // Exercise 6
    private {
        products.push((Product(_name, _id)),
    }*/
    
    function _generateRandomId(string memory _str) private view returns (uint) { //Exercise 7
        uint rand=uint(keccak256(abi.encodePacked(_str))); // Exercise 8
        return(rand%idModulus);        
    }
    // Exercise 8
    function _createRandomProduct(string memory _name) public 
    {
        uint randId = _generateRandomId(_name);
        _createProduct(_name, randId);
    }
    
    // Exercise 9
    event NewProduct(uint ProductId, string name, uint id);
    function _createProduct(string memory _name, uint id) private {
        //uint ArrayProductId=products.push(Product(_name,id)
        //array.push(NewProduct(_arrayProductId,_name));
        products.push(Product(_name,id));
        uint ProductId=(products.length- 1);
        emit NewProduct(ProductId,_name,id);
    }

    // Exercise 10
    mapping(uint=>address) public productToOwner;
    mapping(address=>uint) OwnerProductCount;

    // Exercise 11
    /*function Ownership (uint _ProductId) public {
    productToOwner[msg.sender] = _ProductId ;
    OwnerProductCount += msg.sender; 
    }*/


    // Exercise 12
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
    // Exercise 14
    mapping (uint => uint) public age;
    modifier olderThan (uint _age, uint _userId)
    {
      require( _userId >= _age );
              _;

    }
    function validationUsers( uint _userId) public view olderThan(18,_userId) {

    }

    }
    
    
