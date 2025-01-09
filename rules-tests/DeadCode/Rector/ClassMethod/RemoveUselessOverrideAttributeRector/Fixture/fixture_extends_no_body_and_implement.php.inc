<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ExtendsNoBodyAndImplementInterface
{
    public function foo(): void;
}

abstract class ExtendsNoBodyAndImplementContract
{
    abstract public function bar(): void;
}

final class ExtendsNoBodyAndImplementClass extends ExtendsNoBodyAndImplementContract implements ExtendsNoBodyAndImplementInterface
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

    #[\Override]
    public function baz(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ExtendsNoBodyAndImplementInterface
{
    public function foo(): void;
}

abstract class ExtendsNoBodyAndImplementContract
{
    abstract public function bar(): void;
}

final class ExtendsNoBodyAndImplementClass extends ExtendsNoBodyAndImplementContract implements ExtendsNoBodyAndImplementInterface
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

    public function baz(): void
    {
        echo 'bar';
    }
}
?>
