import { Spinner, Flex } from '@chakra-ui/react';



const Loader = () => {
  return (
    <Flex
      minHeight="calc(100vh - 228px)"
      alignItems="center"
      justifyContent="center"
    >
      <Spinner thickness="4px" color="blue.800" size="xl" label="Loading..." />
    </Flex>
  );
};



export default Loader;
