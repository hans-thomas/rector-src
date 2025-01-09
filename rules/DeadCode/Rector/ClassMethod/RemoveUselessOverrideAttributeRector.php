<?php

declare(strict_types=1);

namespace Rector\DeadCode\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Function_;
use PHPStan\Reflection\ClassReflection;
use Rector\Php80\NodeAnalyzer\PhpAttributeAnalyzer;
use Rector\Rector\AbstractRector;
use Rector\Reflection\ReflectionResolver;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessReturnTagRector\RemoveUselessReturnTagRectorTest
 */
final class RemoveUselessOverrideAttributeRector extends AbstractRector
{
    public function __construct(
        private readonly ReflectionResolver $reflectionResolver,
        private readonly PhpAttributeAnalyzer $phpAttributeAnalyzer,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Remove #[\Override] attribute if method is not exists in parent class',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
interface ParentInterface
{
    public function foo(): void;
}

final class ChildClass implements ParentInterface
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
interface ParentInterface
{
    public function foo(): void;
}

final class ChildClass implements ParentInterface
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    public function bar(): void
    {
        echo 'bar';
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [ClassMethod::class];
    }

    /**
     * @param  ClassMethod|Function_  $node
     */
    public function refactor(Node $node): ?Node
    {
        $classReflection = $this->reflectionResolver->resolveClassReflection($node);
        if (! $classReflection instanceof ClassReflection) {
            return null;
        }

        if (! $classReflection->isClass()) {
            return null;
        }

        if ($classReflection->isInterface()) {
            return null;
        }

        /** @var ClassMethod $node */
        if (! $this->phpAttributeAnalyzer->hasPhpAttribute($node, 'Override')) {
            return null;
        }

        $methodName = $node->name->name;

        // Analyzing phase
        $interfaces = $classReflection->getInterfaces();
        if (count($interfaces) > 0) {
            $notFoundInInterfaces = [];
            foreach ($interfaces as $interfaceReflection) {
                $notFoundInInterfaces[] = $this->findMethod($interfaceReflection, $methodName, $node);
            }
        }

        $parentClass = $classReflection->getParentClass();
        if ($parentClass !== null) {
            $notFoundInParentClass = [];
            $notFoundInParentClass = [$this->findMethod($parentClass, $methodName, $node)];
        }

        // Finding and Removing phase
        /// If method appears in interfaces OR parent class
        if (isset($notFoundInParentClass) && ! isset($notFoundInInterfaces)) {
            $toIterate = $notFoundInParentClass;
        } elseif (isset($notFoundInInterfaces) && ! isset($notFoundInParentClass)) {
            $toIterate = $notFoundInInterfaces;
        } elseif (! isset($notFoundInParentClass) && ! isset($notFoundInInterfaces)) {
            return null;
        }

        /// Removing phase
        if (isset($toIterate)) {
            $this->itemsToRemove($toIterate, $node);

            return $node;
        }
        //// If method appears in both
        ///// Match a method ONLY IF it wasn't found in interfaces AND parent class
        $notFoundInInterfaces ??= [];
        $shouldRemove = array_filter($notFoundInParentClass ?? [], static function ($value) use (
            $notFoundInInterfaces
        ) {
            if (count($value) < 1) {
                return false;
            }

            $k = array_key_first($value);
            $v = $value[$k];

            foreach ($notFoundInInterfaces as $item) {
                if (count($item) === 0) {
                    continue;
                }
                $ik = array_key_first($item);
                $iv = $item[$ik];
                if ($k === $ik && $v === $iv) {
                    return true;
                }
            }

            return false;
        });

        ///// Remove matched items
        $this->itemsToRemove($shouldRemove, $node);

        return $node;
    }

    /**
     * @return array<int,int>
     */
    private function findMethod(
        ClassReflection $reflection,
        string $methodName,
        ClassMethod|Function_ $node
    ): array {
        if (! $reflection->hasMethod($methodName)) {
            foreach ($node->attrGroups as $key => $attrGroup) {
                foreach ($attrGroup->attrs as $attrKey => $attr) {
                    if ($this->isName($attr->name, 'Override')) {
                        return [
                            $key => $attrKey,
                        ];
                    }
                }
            }
        }

        return [];
    }

    /**
     * @param  array<array<int,int>>    $items
     */
    private function itemsToRemove(array $items, ClassMethod|Function_ $node): void
    {
        foreach ($items as $item) {
            if (count($item) > 0) {
                $k = array_key_first($item);
                $v = $item[$k];

                $this->removeAttribute($node, $k, $v);
            }
        }
    }

    private function removeAttribute(ClassMethod|Function_ $node, int|string $key, int|string $attrKey): void
    {
        // Remove Override attribute
        unset($node->attrGroups[$key]->attrs[$attrKey]);

        // Remove empty attribute groups
        /* @phpstan-ignore-next-line */
        if (count($node->attrGroups[$key]->attrs) === 0) {
            unset($node->attrGroups[$key]);
        }
    }
}
