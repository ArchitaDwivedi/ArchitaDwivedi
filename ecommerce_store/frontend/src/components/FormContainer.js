// Designing how the form container component will look i.e any form will
// have this common style

import {Flex} from '@chakra-ui/react';

const FormContainer = ({ children, width = 'xl' }) => {
  return (
    <Flex
      direction="column"
      boxShadow="md"
      rounded="md"
      bgColor="white"
      p="10"
      width={width}
    >
      {children}
    </Flex>
  );
};

export default FormContainer;
