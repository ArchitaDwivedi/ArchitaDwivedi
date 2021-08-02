import {Alert, AlertIcon, AlertTitle} from '@chakra-ui/react';


const Message = ({type= 'info', children}) => {
    return (
        // depending on type, the alert will change
        <Alert status={type}>
            <AlertIcon />
            <AlertTitle>{children}</AlertTitle>
        </Alert>

    );
};

export default Message;