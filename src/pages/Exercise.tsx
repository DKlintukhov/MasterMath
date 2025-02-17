import { Button, Container, OutlinedInput } from "@mui/material";
import { Expression } from "../models";
import { ExpressionInputControl, CountdownTimer } from "../components";
import { useEffect, useState } from "react";

interface Props {
    timeout: number;
    expressions: Expression[];
    onFinished: (duration: number, answers: number[]) => void;
}

function getDurationInSeconds(startDate: Date): number {
    const now = new Date();
    const differenceInMilliseconds = now.getTime() - startDate.getTime();
    return differenceInMilliseconds / 1000;
}

export function Exercise({ timeout, expressions, onFinished }: Props) {
    const [answers, setAnswers] = useState<number[]>(() => Array(expressions.length).fill(null));

    const startDate = new Date();

    useEffect(() => {
        const timerId = setTimeout(() => {
            const duration = getDurationInSeconds(startDate);
            onFinished(duration, answers);
        }, timeout * 60 * 1000);

        return () => clearTimeout(timerId);
    }, [timeout, onFinished]);

    const handleAnswerChange = (id: number, answer: number) => {
        setAnswers(prevAnswers => {
            const newAnswers = [...prevAnswers];
            newAnswers[id] = answer;
            return newAnswers;
        });
    };

    return (
        <Container style={{
            display: "flex",
            flexDirection: "column",
            alignItems: "center",
            justifyContent: "space-evenly",
            height: "100vh"
        }}>
            <CountdownTimer timeout={timeout} onExpired={() => onFinished(getDurationInSeconds(startDate), answers)} />

            <Container
                style={{
                    display: "flex",
                    flexDirection: "column",
                    justifyContent: "center",
                    gap: "5px",
                    overflow: "hidden auto",
                    maxHeight: "70%",
                    minHeight: "15%",
                }}
            >
                {expressions.map((expression, id) => (
                    <Container key={id} style={{
                        display: "flex",
                        alignItems: "center",
                        gap: "5px"
                    }}>
                        <span style={{ width: "25px" }}>{id + 1})</span>
                        <ExpressionInputControl
                            expression={expression}
                            readOnly={true}
                        />
                        <span style={{ width: "7px" }}>=</span>
                        <OutlinedInput
                            style={{ height: "25px", width: "80px" }}
                            size="small"
                            type="number"
                            onBlur={(e) => handleAnswerChange(id, Number(e.target.value))}
                        />
                    </Container>
                ))}
            </Container>

            <Button variant="outlined" onClick={() => {
                const duration = getDurationInSeconds(startDate);
                onFinished(duration, answers);
            }}>Готово</Button>
        </Container >
    );
}
